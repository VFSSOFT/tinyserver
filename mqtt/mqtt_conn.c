
#include "mqtt_conn.h"
#include "mqtt_packets.h"

#include <internal/ts_mem.h>
#include <internal/ts_log.h>

#define MAX_CLIENT_ID_LEN 512

tm_mqtt_conn_t* tm_mqtt_conn__create(tm_server_t* s) {
  tm_mqtt_conn_t* conn;
  
  conn = (tm_mqtt_conn_t*) ts__malloc(sizeof(tm_mqtt_conn_t));
  if (conn == NULL) {
    return NULL;
  }
  memset(conn, 0, sizeof(tm_mqtt_conn_t));

  tm_packet_decoder__set(&(conn->decoder), NULL, 0);
  ts_error__init(&(s->err));

  conn->server = s;
  
  return conn;
}

int tm_mqtt_conn__destroy(tm_mqtt_conn_t* conn) {
  if (conn) {
    if (conn->session) {
      // TODO:
    }
    
    if (conn->in_buf) {
      ts_buf__destroy(conn->in_buf);
    }
    
    ts__free(conn);
  }
  
  return 0;
}

static int tm_mqtt_conn__process_connect(tm_mqtt_conn_t* conn, const char* pkt_bytes, int pkt_bytes_len, int variable_header_off) {
  int err;
  tm_server_t* s = conn->server;
  ts_t* server = s->server;
  int tmp_len;
  const char* tmp_ptr = "";
  int tmp_val;
  int connect_flags = 0;
  char* username = NULL;
  char* password = NULL;
  BOOL auth_ok = FALSE;
  char client_id[MAX_CLIENT_ID_LEN];
  BOOL session_present = FALSE;
  BOOL clean_session;
  tm_packet_decoder_t* decoder = &conn->decoder;

  tm_packet_decoder__set(decoder, pkt_bytes + variable_header_off, pkt_bytes_len - variable_header_off);

  err = tm_packet_decoder__read_int16_string(decoder, &tmp_len, &tmp_ptr);
  if (err || tmp_len != 4 || strcmp(tmp_ptr, "MQTT") != 0) {
    ts_error__set_msg(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Failed to read protocol name");
    goto done;
  }

  err = tm_packet_decoder__read_byte(decoder, &tmp_val);
  if (err || tmp_val != 4) {
    ts_error__set_msg(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Invalid Protocol Level");
    goto done;
  }

  err = tm_packet_decoder__read_byte(decoder, &connect_flags);
  if (err || (connect_flags & 0x01) != 0) {
    ts_error__set_msg(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Invalid Connect Flags");
    goto done;
  }
  clean_session = (connect_flags & 0x02) == 0x02;

  err = tm_packet_decoder__read_int16(decoder, &(conn->keep_alive));
  if (err) {
    ts_error__set_msg(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Invalid Keep Alive");
    goto done;
  }

  err = tm_packet_decoder__read_int16_string(decoder, &tmp_len, &tmp_ptr);
  if (err || tmp_len >= MAX_CLIENT_ID_LEN) {
    ts_error__set_msg(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Invalid Client Id");
    goto done;
  }
  memcpy(client_id, tmp_ptr, tmp_len);
  if (tmp_len == 0) {
    // empty client id
    if (!clean_session) {
      ts_error__set_msg(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Zero client id but want to persist session state");
      goto done;
    }
    //TODO: generate a client id
  } else {
    // TODO: validate the client id
  }
  
  conn->session = tm__find_session(s, client_id);
  session_present = !clean_session && conn->session != NULL;
  
  if (clean_session && conn->session) {
    LOG_DEBUG("[%s] Clear the previous session state", ts_server__get_conn_remote_host(server, conn));
    tm__remove_session(s, conn->session);
    conn->session = NULL;
  }
  if (conn->session == NULL) {
    LOG_DEBUG("[%s] Create new session for the current client", ts_server__get_conn_remote_host(server, conn));
    conn->session = tm__create_session(s, client_id);
    if (conn->session == NULL) {
      ts_error__set(&(conn->err), TS_ERR_OUT_OF_MEMORY);
      goto done;
    }
  }
  conn->session->clean_session = clean_session;

  if ((connect_flags & 0x04) == 0x04) { // will flag
    // TODO: will topic
    err = tm_packet_decoder__read_int16_string(decoder, &tmp_len, &tmp_ptr);
    if (err) {
      ts_error__set_msg(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Invalid Will Topic");
      goto done;
    }

    // TODO: Will Message
    err = tm_packet_decoder__read_int16_string(decoder, &tmp_len, &tmp_ptr);
    if (err) {
      ts_error__set_msg(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Invalid Will Message");
      goto done;
    }
  } else {
    // TODO: validate the Will QoS, Will Retain flags
  }

  if ((connect_flags & 0x40) == 0x40) {
    err = tm_packet_decoder__read_int16_string(decoder, &tmp_len, &tmp_ptr);
    if (err) {
      ts_error__set_msg(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Invalid Will Message");
      goto done;
    }
    
    username = (char*) ts__malloc(tmp_len);
    if (username) {
      ts_error__set(&(conn->err), TS_ERR_OUT_OF_MEMORY);
      goto done;
    }
    memcpy(username, tmp_ptr, tmp_len);
  }
  if ((connect_flags & 0x80) == 0x80) {
    err = tm_packet_decoder__read_int16_string(decoder, &tmp_len, &tmp_ptr);
    if (err) {
      ts_error__set_msg(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Invalid Will Message");
      goto done;
    }
  
    password = (char*) ts__malloc(tmp_len);
    if (password) {
      ts_error__set(&(conn->err), TS_ERR_OUT_OF_MEMORY);
      goto done;
    }
    memcpy(password, tmp_ptr, tmp_len);
  }
  
  // auth user
  s->callbacks.auth_cb(s->callbacks.cb_ctx, s, username, password, &auth_ok);
  
  
done:
  
  if (username) {
    ts__free(username);
  }
  if (password) {
    ts__free(password);
  }
  
  return conn->err.err;
}

static int tm_mqtt_conn__process_in_pkt(tm_mqtt_conn_t* conn, const char* pkt_bytes, int pkt_bytes_len, int variable_header_off) {
  int pkt_type = (pkt_bytes[0] & 0xF0) >> 4;

  if (conn->session == NULL && pkt_type != PKT_TYPE_CONNECT) {
    ts_error__set_msg(&(conn->err), TS_ERR_PROTOCOL_ERROR, "First packet should be CONNECT");
    return TS_ERR_PROTOCOL_ERROR;
  }

  switch (pkt_type) {

    case PKT_TYPE_CONNECT:
      if (conn->session->connected) {
        ts_error__set_msg(&(conn->err), TS_ERR_PROTOCOL_ERROR, "Already connected but receive another CONNECT");
        return TS_ERR_PROTOCOL_ERROR;
      }

      return tm_mqtt_conn__process_connect(conn, pkt_bytes, pkt_bytes_len, variable_header_off);

    case PKT_TYPE_CONNACK:
      break;

    case PKT_TYPE_PUBLISH:
      break;

    case PKT_TYPE_PUBACK:
      break;

    case PKT_TYPE_PUBREC:
      break;

    case PKT_TYPE_PUBREL:
      break;

    case PKT_TYPE_PUBCOMP:
      break;

    case PKT_TYPE_SUBSCRIBE:
      break;

    case PKT_TYPE_SUBACK:
      break;

    case PKT_TYPE_UNSUBSCRIBE:
      break;

    case PKT_TYPE_UNSUBACK:
      break;

    case PKT_TYPE_PINGREQ:
      break;

    case PKT_TYPE_PINGRESP:
      break;

    case PKT_TYPE_DISCONNECT:
      break;

    default:
      ts_error__set_msgf(&(conn->err), TS_ERR_MALFORMED_MQTT_PACKET, "Unkonwn Control Packet Type(%d)", pkt_type);
      return TS_ERR_MALFORMED_MQTT_PACKET;
  }
  return 0;
}
int tm_mqtt_conn__data_in(tm_mqtt_conn_t* conn, const char* data, int len) {
  int err;
  int total_bytes_consumed = 0;
  BOOL parsed = FALSE;
  int pkt_bytes_cnt = 0;
  unsigned int remaining_length = 0;
  BOOL use_in_buf = FALSE;
  const char* buf;
  int buf_len;

  if (ts_buf__get_length(conn->in_buf) == 0) {
    buf = data;
    buf_len = len;
    use_in_buf = FALSE;
  } else {
    ts_buf__write(conn->in_buf, data, len);
    buf = conn->in_buf->buf;
    buf_len = conn->in_buf->len;
    use_in_buf = TRUE;
  }

  while (1) {
    ts_error__reset(&(conn->err));
    parsed = tm__parse_packet(buf, buf_len, &pkt_bytes_cnt, &remaining_length, &conn->err);

    if (conn->err.err) { // check the parse error first
      goto done;
    }

    if (!parsed) {
      if (use_in_buf) {
        ts_buf__read(conn->in_buf, NULL, &total_bytes_consumed);
      } else {
        // append the left data to the in_buf
        ts_buf__write(conn->in_buf, buf, buf_len);
      }

      goto done; // more data is expected, do nothing now
    }

    // parse successfully
    err = tm_mqtt_conn__process_in_pkt(conn, buf, pkt_bytes_cnt, pkt_bytes_cnt - remaining_length);
    if (err) {
      goto done;
    }

    buf += pkt_bytes_cnt;
    buf_len -= pkt_bytes_cnt;
    total_bytes_consumed += pkt_bytes_cnt;
  }

done:
  if (conn->err.err) {
    // TODO: disconnect from the client
  }
}
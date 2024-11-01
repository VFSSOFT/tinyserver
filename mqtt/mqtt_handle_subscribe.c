#include "mqtt_conn.h"
#include "mqtt_utils.h"

#include <internal/ts_log.h>
#include <internal/ts_miscellany.h>

static int tm_mqtt_conn__send_suback(ts_t* server, ts_conn_t* c, int pkt_id, char* return_codes, int return_code_count) {
  tm_mqtt_conn_t* conn = ts_server__get_conn_user_data(server, c);
  char suback[64];
  suback[0] = (char)0x90;
  suback[1] = (char)(2 + return_code_count);
  uint162bytes_be(pkt_id, suback+2);
  memcpy(suback + 4, return_codes, return_code_count);
  
  LOG_DUMP(suback, 4 + return_code_count, "[%s][%s] Send [SUBACK]", ts_server__get_conn_remote_host(server, c), conn->session->client_id);

  return tm_mqtt_conn__send_packet(server, c, suback, 4 + return_code_count, pkt_id, NULL);
}

int tm_mqtt_conn__process_subscribe(ts_t* server, ts_conn_t* c, const char* pkt_bytes, int pkt_bytes_len, int variable_header_off) {
  int err;
  tm_mqtt_conn_t* conn;
  tm_server_t* s;
  tm_packet_decoder_t* decoder;
  ts_error_t errt;
  const char* tmp_ptr = "";
  int tmp_val, tmp_len, pkt_id, granted_qos, request_qos;
  char topic[65536];
  char return_codes[32]; // at most 32
  int return_codes_count = 0;
  const char* conn_id;
  
  conn = (tm_mqtt_conn_t*) ts_server__get_conn_user_data(server, c);
  conn_id = ts_server__get_conn_remote_host(server, c);
  s = conn->server;
  decoder = &conn->decoder;
  
  LOG_DUMP(pkt_bytes, pkt_bytes_len, "[%s][%s] Receive [SUBSCRIBE]", conn_id, conn->session->client_id);
  
  ts_error__init(&errt);
  tm_packet_decoder__set(decoder, pkt_bytes + variable_header_off, pkt_bytes_len - variable_header_off);
  
  err = tm_packet_decoder__read_int16(decoder, &pkt_id);
  if (err || pkt_id <= 0) {
    LOG_ERROR("[%s][%s] Invalid Packet Identifier", conn_id, conn->session->client_id);
    tm_mqtt_conn__abort(server, c);
    goto done;
  }
  
  while (tm_packet_decoder__available(decoder) > 0) {
    err = tm_packet_decoder__read_int16_string(decoder, &tmp_len, &tmp_ptr);
    if (err) {
      LOG_ERROR("[%s][%s] Invalid Topic Filter", conn_id, conn->session->client_id);
      tm_mqtt_conn__abort(server, c);
      goto done;
    }
  
    err = tm_topics__valid_topic_filter(tmp_ptr, tmp_len, &errt);
    if (err) {
      LOG_ERROR("[%s][%s] Invalid Topic Filter: %s", conn_id, conn->session->client_id, errt.msg);
      tm_mqtt_conn__abort(server, c);
      goto done;
    }
    
    memcpy(topic, tmp_ptr, tmp_len);
    topic[tmp_len] = 0;
  
    err = tm_packet_decoder__read_byte(decoder, &request_qos);
    if (err || !tm__is_valid_qos(request_qos)) {
      LOG_ERROR("[%s][%s] Invalid QoS", conn_id, conn->session->client_id);
      tm_mqtt_conn__abort(server, c);
      goto done;
    }
    
    granted_qos = request_qos;
    tm__internal_subscribe_cb(s, c, topic, request_qos, &granted_qos);
    return_codes[return_codes_count++] = (char)granted_qos;
    LOG_VERB(
        "[%s][%s] Subscribe: Topic='%s', RequestQoS=%d, GrantedQoS=%d",
        conn_id,
        conn->session->client_id,
        topic,
        request_qos,
        granted_qos
    );
    
    if (tm__is_valid_qos(granted_qos)) {
      err = tm__on_subscription(s, c, topic, granted_qos);
      if (err) {
        tm_mqtt_conn__abort(server, c);
        goto done;
      }
    }
    
  }
  
  if (return_codes_count == 0) {
    LOG_ERROR("[%s][%s] No Topic filter/Request QoS in the Subscribe packet", conn_id, conn->session->client_id);
    tm_mqtt_conn__abort(server, c);
    goto done;
  }
  
  err = tm_mqtt_conn__send_suback(server, c, pkt_id, return_codes, return_codes_count);
  if (err) {
    LOG_ERROR("[%s][%s] Fail to send SUBACK", conn_id, conn->session->client_id);
    tm_mqtt_conn__abort(server, c);
    goto done;
  }
  
done:
  return 0;
}


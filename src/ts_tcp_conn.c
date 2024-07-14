
#include "ts_internal.h"

int ts_conn__init(ts_server_listener_t* listener, ts_conn_t* conn) {
  int err;
  
  conn->listener = listener;
  conn->write_reqs = NULL;
  
  switch (listener->config->protocol) {
    case TS_PROTO_TCP:
      conn->tls = NULL;
      break;
      
    case TS_PROTO_TLS:
      conn->tls = (ts_tls_t*) ts__malloc(sizeof(ts_tls_t));
      if (conn->tls == NULL) {
        err = TS_ERR_OUT_OF_MEMORY;
        goto done;
      }
      
      err = ts_tls__init(conn->tls);
      if (err) {
        goto done;
      }
      
      err = ts_tls__set_cert_files(conn->tls, listener->config->cert, listener->config->key);
      if (err) {
        goto done;
      }
      
      err = ts_tls__set_verify_mode(conn->tls, listener->config->tls_verify_mode);
      if (err) {
        goto done;
      }
      
      break;
  }
  
  err = uv_tcp_init(listener->uvloop, &conn->uvtcp);
  if (err) {
    return err;
  }
  
done:
  
  return 0;
}

int ts_conn__destroy(ts_server_listener_t* listener, ts_conn_t* conn) {
  if (conn->tls) {
    ts_tls__destroy(conn->tls);
    ts__free(conn->tls);
  }
  return 0;
}

ts_conn_write_req_t* ts_conn__create_write_req(ts_conn_t* conn, char* data, int len) {
  ts_conn_write_req_t* req = (ts_conn_write_req_t*) ts__malloc(sizeof(ts_conn_write_req_t));
  if (req == NULL) {
    return NULL;
  }
  
  req->conn = conn;
  req->buf = uv_buf_init(data, len);
  DL_APPEND(conn->write_reqs, req);
  
  return req;
}

void ts_conn__destroy_write_req(ts_conn_t* conn, ts_conn_write_req_t* req) {
  DL_DELETE(conn->write_reqs, req);
  
  ts__free(req->buf.base);
  ts__free(req);
}
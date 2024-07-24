#include "ts_internal.h"

static void uv_on_idle(uv_idle_t *handle) {
  ts_server_t* server = CONTAINER_OF(handle, ts_server_t, uvidle);
  server->idle_cb(server->cb_ctx, server);
}

int ts_server_idle__init(ts_server_t* server) {
  int err;
  err = uv_idle_init(server->uvloop, &server->uvidle);
  return err;
}

int ts_server_idle__start(ts_server_t* server) {
  int err;
  err = uv_idle_start(&(server->uvidle), uv_on_idle);
  return err;
}

int ts_server_idle__stop(ts_server_t* server) {
  int err;
  err = uv_idle_stop(&server->uvidle);
  return err;
}
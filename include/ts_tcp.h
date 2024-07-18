#ifndef TINYSERVER_TS_TCP_H
#define TINYSERVER_TS_TCP_H

#include <uv.h>

#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/conf.h>
#include <openssl/engine.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TS_EXTERN /* nothing */

#define TS_DEFAULT_BACKLOG 128

#define TS_ERR_OUT_OF_MEMORY 0x80000001


typedef struct ts_error_s ts_error_t;
typedef struct ts_buf_s ts_buf_t;
typedef struct ts_ro_buf_s ts_ro_buf_t;
typedef struct ts_server_listener_config_s ts_server_listener_config_t;
typedef struct ts_server_config_s ts_server_config_t;
typedef struct ts_server_listener_s ts_server_listener_t;
typedef struct ts_server_s ts_server_t;
typedef struct ts_conn_write_req_s ts_conn_write_req_t;
typedef struct ts_conn_s ts_conn_t;
typedef struct ts_tls_s ts_tls_t;
typedef struct ts_log_s ts_log_t;

typedef int (*ts_server_connected_cb)(void* ctx, ts_server_t* server, ts_conn_t* conn, int status);
typedef int (*ts_server_disconnected_cb)(void* ctx, ts_server_t* server, ts_conn_t* conn, int status);
typedef int (*ts_server_read_cb)(void* ctx, ts_server_t* server, ts_conn_t* conn, const char* data, int len);
typedef int (*ts_server_write_cb)(void* ctx, ts_server_t* server, ts_conn_t* conn, int status, int can_write_more);
typedef int (*ts_server_idle_cb)(void* ctx, ts_server_t* server);

typedef int (*ts_log_cb)(void* ctx, int level, const char* msg);

TS_EXTERN  int ts_server_listener_config__init(ts_server_listener_config_t* cfg);

TS_EXTERN int ts_server__init(ts_server_t* server);
TS_EXTERN int ts_server__destroy(ts_server_t server);
TS_EXTERN int ts_server__set_cb_ctx(ts_server_t* server, void* ctx);
TS_EXTERN int ts_server__set_connected_cb(ts_server_t* server, ts_server_connected_cb cb);
TS_EXTERN int ts_server__set_disconnected_cb(ts_server_t* server, ts_server_disconnected_cb cb);
TS_EXTERN int ts_server__set_read_cb(ts_server_t* server, ts_server_read_cb cb);
TS_EXTERN int ts_server__set_write_cb(ts_server_t* server, ts_server_write_cb cb);
TS_EXTERN int ts_server__set_idle_cb(ts_server_t* server, ts_server_idle_cb cb);
TS_EXTERN int ts_server__set_config(ts_server_t* server, ts_server_config_t* cfg);
TS_EXTERN int ts_server__start(ts_server_t* server);
TS_EXTERN int ts_server__run(ts_server_t* server);
TS_EXTERN int ts_server__stop(ts_server_t* server);
TS_EXTERN int ts_server__write(ts_server_t* server, ts_conn_t* conn, const char* data, int len);
TS_EXTERN int ts_server__disconnect(ts_server_t* server, ts_conn_t* conn);

TS_EXTERN  int ts_server_log_set_log_level(ts_server_t* server, int log_level);
TS_EXTERN  int ts_server_log_set_log_dest(ts_server_t* server, int dest);
TS_EXTERN  int ts_server_log_set_log_dir(ts_server_t* server, const char* dir);
TS_EXTERN  int ts_server_log_set_log_cb(ts_server_t* server, void* ctx, ts_log_cb cb);

struct ts_error_s {
    int err;
    char* msg;
};

struct ts_buf_s {
    char* buf;
    int   len;
    int   cap;
    int   const_ref; // whether the buf is a const ref to another memory
};

// readonly buf
struct ts_ro_buf_s {
    const char* buf;
    int len;
};

#define TS_LOG_DEST_STDOUT 1
#define TS_LOG_DEST_FILE   2
#define TS_LOG_DEST_EVENT  4

#define TS_LOG_LEVEL_NONE    0
#define TS_LOG_LEVEL_ERROR   1
#define TS_LOG_LEVEL_INFO    2
#define TS_LOG_LEVEL_VERB    3
#define TS_LOG_LEVEL_DEBUG   4
#define TS_LOG_LEVEL_DEBUGEX 5

struct ts_log_s {
    int log_level;
    int log_dest;
    char* log_dir;
    void* log_ctx;
    ts_log_cb log_cb;
};

#define TS_PROTO_TCP   1
#define TS_PROTO_TLS  2

struct ts_server_listener_config_s {
    const char* host;
    int port;
    int use_ipv6;
    int backlog;
    int protocol;
    
    const char* cert;
    const char* key;
    int tls_verify_mode;
};
struct ts_server_config_s {
    ts_server_listener_config_t* listeners;
    int listeners_count;
};

struct ts_server_listener_s {
    uv_tcp_t uvtcp;
    uv_loop_t *uvloop;
    ts_server_t* server;
  
    ts_server_listener_config_t* config;
};
struct ts_server_s {
    ts_server_listener_t* listeners;
    int listener_count;
    
    ts_server_connected_cb connected_cb;
    ts_server_disconnected_cb disconnected_cb;
    ts_server_read_cb read_cb;
    ts_server_write_cb write_cb;
    ts_server_idle_cb idle_cb;
    void* cb_ctx;
  
    uv_idle_t uvidle;
    uv_loop_t *uvloop;
    
    ts_conn_t* conns;
    ts_server_config_t config;
    ts_log_t log;
    char* err_msg;
};

struct ts_conn_write_req_s {
    uv_write_t req;
    uv_buf_t buf;
    
    ts_conn_t* conn;
    
    ts_conn_write_req_t* prev;
    ts_conn_write_req_t* next;
};

struct ts_conn_s {
    uv_tcp_t uvtcp;
    uv_loop_t* uvloop;
    ts_server_listener_t* listener;
    
    ts_conn_write_req_t* write_reqs;
    
    ts_tls_t* tls;
    
    ts_conn_t* prev;
    ts_conn_t* next;
};

#define TLS_STATE_HANDSHAKING  1
#define TLS_STATE_CONNECTED    2
#define TLS_STATE_DISCONNECTED 3

struct ts_tls_s {
    BIO*     appbio; // Application BIO, all IO should be done by this
    BIO*     sslbio; // SSL BIO, only used by OpenSSL
    SSL*     ssl;
    SSL_CTX* ctx;
    int      ssl_state;
    int      ssl_err;

    ts_buf_t* ssl_buf; // used internal
};

#ifdef __cplusplus
}
#endif

#endif //TINYSERVER_TS_TCP_H

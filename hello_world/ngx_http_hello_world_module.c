#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_log.h>

#define HELLO_WORLD "hello world~!!!"

static u_char ngx_hello_world[] = HELLO_WORLD;

static char *ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r);

/* Module directives */
static ngx_command_t ngx_http_hello_world_commands[] = {
    {
        ngx_string("hello_world"),          /* Directive name */
        NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,  /* location and argument type */
        ngx_http_hello_world,               /* configuration function */
        0,                                  /* configuration store location */
        0,                                  /* keyword store location on struct */
        NULL                                /* default NULL */
    },
    ngx_null_command                        /* command termination */
};

/* Module context */
static ngx_http_module_t ngx_http_hello_world_module_ctx = {
    NULL,                                   /* preconfiguration */
    NULL,                                   /* postconfiguration */

    NULL,                                   /* create main configuration */
    NULL,                                   /* init main configuration */

    NULL,                                   /* create server configuration */
    NULL,                                   /* merge server configuration */

    NULL,                                   /* create location configuration */
    NULL                                    /* merge location configuration */
};

/* Module definition */
ngx_module_t ngx_http_hello_world_module = {
    NGX_MODULE_V1,                          /* module version */
    &ngx_http_hello_world_module_ctx,       /* module context */
    ngx_http_hello_world_commands,          /* module directives */
    NGX_HTTP_MODULE,                        /* module type */
    NULL,                                   /* init master */
    NULL,                                   /* init module */
    NULL,                                   /* init process */
    NULL,                                   /* init thread */
    NULL,                                   /* exit thread */
    NULL,                                   /* exit process */
    NULL,                                   /* exit master */
    NGX_MODULE_V1_PADDING
};

/* Handler */
static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r)
{
    ngx_buf_t *b;
    ngx_chain_t out;

    /* Set and send, HTTP request header */
    r->headers_out.content_length_n = sizeof(ngx_hello_world);
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char *) "text/plain";
    r->headers_out.status = NGX_HTTP_OK;

    ngx_http_send_header(r);


    /* Set and send, HTTP request body */
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    out.buf = b;
    out.next = NULL;
    b->pos = ngx_hello_world;
    b->last = ngx_hello_world + sizeof(ngx_hello_world);
    b->memory = 1;
    b->last_buf = 1;

    ngx_log_error(NGX_LOG_INFO, r->connection->log, 0, "Sent response '%s'", HELLO_WORLD);
    return ngx_http_output_filter(r, &out);
}

/* Handler register */
static char *ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_hello_world_handler;

    return NGX_CONF_OK;
}

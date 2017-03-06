/**
 *    Copyright(c) 2016-2017 rryqszq4
 *
 *
 */


#ifndef NGX_HTTP_PHP_HANDLER_H
#define NGX_HTTP_PHP_HANDLER_H

#include <nginx.h>
#include <ngx_http.h>

#include "ngx_http_php_module.h"

// handler
//ngx_int_t ngx_http_php_init_handler(ngx_conf_t *cf, ngx_http_php_main_conf_t *pmcf);

ngx_int_t ngx_http_php_post_read_handler(ngx_http_request_t *r);
void ngx_http_php_request_cleanup_handler(void *data);

ngx_int_t ngx_http_php_rewrite_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_php_rewrite_file_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_php_rewrite_inline_handler(ngx_http_request_t *r);

ngx_int_t ngx_http_php_access_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_php_access_file_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_php_access_inline_handler(ngx_http_request_t *r);

ngx_int_t ngx_http_php_content_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_php_content_file_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_php_content_inline_handler(ngx_http_request_t *r);

ngx_int_t ngx_http_php_content_post_handler(ngx_http_request_t *r);

//ngx_int_t ngx_http_php_content_async_handler(ngx_http_request_t *r);
//ngx_int_t ngx_http_php_content_async_inline_handler(ngx_http_request_t *r);
//void *ngx_http_php_async_inline_thread(void *arg);

//ngx_int_t ngx_http_php_content_sync_inline_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_php_content_thread_inline_handler(ngx_http_request_t *r);
void *ngx_http_php_sync_inline_thread(void *arg);
ngx_int_t ngx_http_php_content_thread_file_handler(ngx_http_request_t *r);
void *ngx_http_php_sync_file_thread(void *arg);

ngx_int_t ngx_http_php_content_thread_inline_handler_1(ngx_http_request_t *r);
void *ngx_http_php_content_inline_thread_routine(void *data, ngx_log_t *log);
void *ngx_http_php_content_thread_event_handler(ngx_event_t *ev);

ngx_int_t ngx_http_php_log_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_php_log_file_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_php_log_inline_handler(ngx_http_request_t *r);

ngx_int_t ngx_http_php_set_inline_handler(ngx_http_request_t *r, ngx_str_t *val, ngx_http_variable_value_t *v, void *data);
ngx_int_t ngx_http_php_set_run_inline_handler(ngx_http_request_t *r, ngx_str_t *val, ngx_http_variable_value_t *v, void *data);
ngx_int_t ngx_http_php_set_file_handler(ngx_http_request_t *r, ngx_str_t *val, ngx_http_variable_value_t *v, void *data);
ngx_int_t ngx_http_php_set_run_file_handler(ngx_http_request_t *r, ngx_str_t *val, ngx_http_variable_value_t *v, void *data);

#endif
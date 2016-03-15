/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */


#ifndef NGX_HTTP_PHP_HANDLER_H
#define NGX_HTTP_PHP_HANDLER_H

#include <nginx.h>
#include <ngx_http.h>

// handler
ngx_int_t ngx_http_php_content_handler(ngx_http_request_t *r);

ngx_int_t ngx_http_php_content_file_handler(ngx_http_request_t *r);

ngx_int_t ngx_http_php_content_inline_handler(ngx_http_request_t *r);


#endif
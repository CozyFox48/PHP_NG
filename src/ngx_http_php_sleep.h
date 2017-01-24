/**
 *    Copyright(c) 2016-2017 rryqszq4
 *
 *
 */

#ifndef NGX_HTTP_PHP_SLEEP_H
#define NGX_HTTP_PHP_SLEEP_H

#include "ngx_http_php_module.h"

ngx_int_t ngx_http_php_sleep_run(ngx_http_request_t *r);

void ngx_http_php_sleep_handler(ngx_event_t *ev);

#endif
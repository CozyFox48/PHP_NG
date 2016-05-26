/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#ifndef NGX_HTTP_PHP_MODULE_H
#define NGX_HTTP_PHP_MODULE_H

#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_config.h>
#include <nginx.h>

#if defined(NDK) && NDK
#include <ndk.h>
#endif

#include "ngx_http_php_core.h"

#define MODULE_NAME "php_nginx_module"
#define MODULE_VERSION	"0.0.3"

extern ngx_module_t	ngx_http_php_module;
ngx_http_request_t *ngx_php_request;

typedef struct {

	ngx_str_t ini_path;
	ngx_http_php_code_t *init_code;
	ngx_http_php_code_t *init_inline_code;

	unsigned enabled_rewrite_handler:1;
	unsigned enabled_access_handler:1;
	unsigned enabled_content_handler:1;

	ngx_http_php_state_t *state;

} ngx_http_php_main_conf_t;

typedef struct {
	ngx_str_t document_root;

	ngx_http_php_code_t *rewrite_code;
	ngx_http_php_code_t *rewrite_inline_code;
	ngx_http_php_code_t *access_code;
	ngx_http_php_code_t *access_inline_code;
	ngx_http_php_code_t *content_code;
	ngx_http_php_code_t *content_inline_code;

	ngx_int_t (*rewrite_handler)(ngx_http_request_t *r);
	ngx_int_t (*access_handler)(ngx_http_request_t *r);
	ngx_int_t (*content_handler)(ngx_http_request_t *r);
} ngx_http_php_loc_conf_t;

#endif
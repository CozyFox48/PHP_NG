/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#ifndef _PHP_NGX_TIME_H_
#define _PHP_NGX_TIME_H_

#include <ngx_http.h>

#include <php.h>
#include <php_ini.h>
#include <ext/standard/info.h>

PHP_METHOD(ngx_time, sleep);

void php_ngx_time_init(int module_number TSRMLS_DC);

#endif
/**
 *    Copyright(c) 2016-2017 rryqszq4
 *
 *
 */

#include "php_ngx_log.h"
#include "../ngx_http_php_module.h"

static zend_class_entry *php_ngx_class_entry;

ZEND_BEGIN_ARG_INFO_EX(ngx_exit_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0, status)
ZEND_END_ARG_INFO()

PHP_METHOD(ngx, _exit)
{
    long status = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &status) == FAILURE){
        RETURN_NULL();
    }

    EG(exit_status) = status;

    zend_bailout();
}

static const zend_function_entry php_ngx_class_functions[] = {
    PHP_ME(ngx, _exit, ngx_exit_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    {NULL, NULL, NULL, 0, 0}
};

void php_ngx_core_init(int module_number TSRMLS_DC)
{
    zend_class_entry ngx_class_entry;
    INIT_CLASS_ENTRY(ngx_class_entry, "ngx", php_ngx_class_functions);
    php_ngx_class_entry = zend_register_internal_class(&ngx_class_entry TSRMLS_CC);

    zend_declare_class_constant_long(php_ngx_class_entry, "OK", sizeof("OK")-1, NGX_OK TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "ERROR", sizeof("ERROR")-1, NGX_ERROR TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "AGAIN", sizeof("AGAIN")-1, NGX_AGAIN TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "BUSY", sizeof("BUSY")-1, NGX_BUSY TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "DONE", sizeof("DONE")-1, NGX_DONE TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "DECLINED", sizeof("DECLINED")-1, NGX_DECLINED TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "ABORT", sizeof("ABORT")-1, NGX_ABORT TSRMLS_CC);

    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_CONTINUE", sizeof("HTTP_CONTINUE")-1, NGX_HTTP_CONTINUE TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_SWITCHING_PROTOCOLS", sizeof("HTTP_SWITCHING_PROTOCOLS")-1, NGX_HTTP_SWITCHING_PROTOCOLS TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_PROCESSING", sizeof("HTTP_PROCESSING")-1, NGX_HTTP_PROCESSING TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_OK", sizeof("HTTP_OK")-1, NGX_HTTP_OK TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_CREATED", sizeof("HTTP_CREATED")-1, NGX_HTTP_CREATED TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_ACCEPTED", sizeof("HTTP_ACCEPTED")-1, NGX_HTTP_ACCEPTED TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_NO_CONTENT", sizeof("HTTP_NO_CONTENT")-1, NGX_HTTP_NO_CONTENT TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_PARTIAL_CONTENT", sizeof("HTTP_PARTIAL_CONTENT")-1, NGX_HTTP_PARTIAL_CONTENT TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_SPECIAL_RESPONSE", sizeof("HTTP_SPECIAL_RESPONSE")-1, NGX_HTTP_SPECIAL_RESPONSE TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_MOVED_PERMANENTLY", sizeof("HTTP_MOVED_PERMANENTLY")-1, NGX_HTTP_MOVED_PERMANENTLY TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_MOVED_TEMPORARILY", sizeof("HTTP_MOVED_TEMPORARILY")-1, NGX_HTTP_MOVED_TEMPORARILY TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_SEE_OTHER", sizeof("HTTP_SEE_OTHER")-1, NGX_HTTP_SEE_OTHER TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_NOT_MODIFIED", sizeof("HTTP_NOT_MODIFIED")-1, NGX_HTTP_NOT_MODIFIED TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_TEMPORARY_REDIRECT", sizeof("HTTP_TEMPORARY_REDIRECT")-1, NGX_HTTP_TEMPORARY_REDIRECT TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_BAD_REQUEST", sizeof("HTTP_BAD_REQUEST")-1, NGX_HTTP_BAD_REQUEST TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_UNAUTHORIZED", sizeof("HTTP_UNAUTHORIZED")-1, NGX_HTTP_UNAUTHORIZED TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_FORBIDDEN", sizeof("HTTP_FORBIDDEN")-1, NGX_HTTP_FORBIDDEN TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_NOT_FOUND", sizeof("HTTP_NOT_FOUND")-1, NGX_HTTP_NOT_FOUND TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_NOT_ALLOWED", sizeof("HTTP_NOT_ALLOWED")-1, NGX_HTTP_NOT_ALLOWED TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_REQUEST_TIME_OUT", sizeof("HTTP_REQUEST_TIME_OUT")-1, NGX_HTTP_REQUEST_TIME_OUT TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_CONFLICT", sizeof("HTTP_CONFLICT")-1, NGX_HTTP_CONFLICT TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_LENGTH_REQUIRED", sizeof("HTTP_LENGTH_REQUIRED")-1, NGX_HTTP_LENGTH_REQUIRED TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_PRECONDITION_FAILED", sizeof("HTTP_PRECONDITION_FAILED")-1, NGX_HTTP_PRECONDITION_FAILED TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_REQUEST_ENTITY_TOO_LARGE", sizeof("HTTP_REQUEST_ENTITY_TOO_LARGE")-1, NGX_HTTP_REQUEST_ENTITY_TOO_LARGE TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_REQUEST_URI_TOO_LARGE", sizeof("HTTP_REQUEST_URI_TOO_LARGE")-1, NGX_HTTP_REQUEST_URI_TOO_LARGE TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_UNSUPPORTED_MEDIA_TYPE", sizeof("HTTP_UNSUPPORTED_MEDIA_TYPE")-1, NGX_HTTP_UNSUPPORTED_MEDIA_TYPE TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_RANGE_NOT_SATISFIABLE", sizeof("HTTP_RANGE_NOT_SATISFIABLE")-1, NGX_HTTP_RANGE_NOT_SATISFIABLE TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_CLOSE", sizeof("HTTP_CLOSE")-1, NGX_HTTP_CLOSE TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_NGINX_CODES", sizeof("HTTP_NGINX_CODES")-1, NGX_HTTP_NGINX_CODES TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_REQUEST_HEADER_TOO_LARGE", sizeof("HTTP_REQUEST_HEADER_TOO_LARGE")-1, NGX_HTTP_REQUEST_HEADER_TOO_LARGE TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTPS_CERT_ERROR", sizeof("HTTPS_CERT_ERROR")-1, NGX_HTTPS_CERT_ERROR TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTPS_NO_CERT", sizeof("HTTPS_NO_CERT")-1, NGX_HTTPS_NO_CERT TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_TO_HTTPS", sizeof("HTTP_TO_HTTPS")-1, NGX_HTTP_TO_HTTPS TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_CLIENT_CLOSED_REQUEST", sizeof("HTTP_CLIENT_CLOSED_REQUEST")-1, NGX_HTTP_CLIENT_CLOSED_REQUEST TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_INTERNAL_SERVER_ERROR", sizeof("HTTP_INTERNAL_SERVER_ERROR")-1, NGX_HTTP_INTERNAL_SERVER_ERROR TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_NOT_IMPLEMENTED", sizeof("HTTP_NOT_IMPLEMENTED")-1, NGX_HTTP_NOT_IMPLEMENTED TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_BAD_GATEWAY", sizeof("HTTP_BAD_GATEWAY")-1, NGX_HTTP_BAD_GATEWAY TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_SERVICE_UNAVAILABLE", sizeof("HTTP_SERVICE_UNAVAILABLE")-1, NGX_HTTP_SERVICE_UNAVAILABLE TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_GATEWAY_TIME_OUT", sizeof("HTTP_GATEWAY_TIME_OUT")-1, NGX_HTTP_GATEWAY_TIME_OUT TSRMLS_CC);
    zend_declare_class_constant_long(php_ngx_class_entry, "HTTP_INSUFFICIENT_STORAGE", sizeof("HTTP_INSUFFICIENT_STORAGE")-1, NGX_HTTP_INSUFFICIENT_STORAGE TSRMLS_CC);

}





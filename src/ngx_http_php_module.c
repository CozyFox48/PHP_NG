/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_conf_file.h>
#include <nginx.h>

#include "php/php_ngx.h"

#include "ngx_http_php_module.h"
#include "ngx_http_php_directive.h"
#include "ngx_http_php_handler.h"

// http init
static ngx_int_t ngx_http_php_init(ngx_conf_t *cf);
static ngx_int_t ngx_http_php_handler_init(ngx_http_core_main_conf_t *cmcf, ngx_http_php_main_conf_t *pmcf);

static void *ngx_http_php_create_main_conf(ngx_conf_t *cf);
static char *ngx_http_php_init_main_conf(ngx_conf_t *cf, void *conf);

static void *ngx_http_php_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_php_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child); 

// function init
static ngx_int_t ngx_http_php_init_worker(ngx_cycle_t *cycle);
static void ngx_http_php_exit_worker(ngx_cycle_t *cycle);

static ngx_command_t ngx_http_php_commands[] = {

	{ngx_string("php_ini_path"),
	 NGX_HTTP_MAIN_CONF|NGX_CONF_TAKE1,
	 ngx_http_php_ini_path,
	 NGX_HTTP_MAIN_CONF_OFFSET,
	 0,
	 NULL
	},

	{ngx_string("php_init_code"),
	 NGX_HTTP_MAIN_CONF|NGX_CONF_TAKE1,
	 ngx_http_php_init_inline_phase,
	 NGX_HTTP_MAIN_CONF_OFFSET,
	 0,
	 NULL
	},

	{ngx_string("php_init_file"),
	 NGX_HTTP_MAIN_CONF|NGX_CONF_TAKE1,
	 ngx_http_php_init_file_phase,
	 NGX_HTTP_MAIN_CONF_OFFSET,
	 0,
	 NULL
	},

	{ngx_string("php_rewrite_handler"),
	 NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
	 	|NGX_CONF_TAKE1,
	 ngx_http_php_rewrite_phase,
	 NGX_HTTP_LOC_CONF_OFFSET,
	 0,
	 ngx_http_php_rewrite_file_handler
	},

	{ngx_string("php_rewrite_handler_code"),
	 NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
	 	|NGX_CONF_TAKE1,
	 ngx_http_php_rewrite_inline_phase,
	 NGX_HTTP_LOC_CONF_OFFSET,
	 0,
	 ngx_http_php_rewrite_inline_handler
	},

	{ngx_string("php_access_handler"),
	 NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
	 	|NGX_CONF_TAKE1,
	 ngx_http_php_access_phase,
	 NGX_HTTP_LOC_CONF_OFFSET,
	 0,
	 ngx_http_php_access_file_handler
	},

	{ngx_string("php_access_handler_code"),
	 NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
	 	|NGX_CONF_TAKE1,
	 ngx_http_php_access_inline_phase,
	 NGX_HTTP_LOC_CONF_OFFSET,
	 0,
	 ngx_http_php_access_inline_handler
	},

	{ngx_string("php_content_handler"),
	 NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
	 	|NGX_CONF_TAKE1,
	 ngx_http_php_content_phase,
	 NGX_HTTP_LOC_CONF_OFFSET,
	 0,
	 ngx_http_php_content_file_handler
	},

	{ngx_string("php_content_handler_code"),
	 NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
	 	|NGX_CONF_TAKE1,
	 ngx_http_php_content_inline_phase,
	 NGX_HTTP_LOC_CONF_OFFSET,
	 0,
	 ngx_http_php_content_inline_handler
	},

	ngx_null_command
};

static ngx_http_module_t ngx_http_php_module_ctx = {
	NULL,                          /* preconfiguration */
	ngx_http_php_init,             /* postconfiguration */

	ngx_http_php_create_main_conf, /* create main configuration */
	ngx_http_php_init_main_conf,   /* init main configuration */

	NULL,                          /* create server configuration */
	NULL,                          /* merge server configuration */

	ngx_http_php_create_loc_conf,  /* create location configuration */
	ngx_http_php_merge_loc_conf    /* merge location configuration */

};


ngx_module_t ngx_http_php_module = {
	NGX_MODULE_V1,
	&ngx_http_php_module_ctx,    /* module context */
	ngx_http_php_commands,       /* module directives */
	NGX_HTTP_MODULE,               /* module type */
	NULL,                          /* init master */
	NULL,                          /* init module */
	ngx_http_php_init_worker,      /* init process */
	NULL,                          /* init thread */
	NULL,                          /* exit thread */
	ngx_http_php_exit_worker,      /* exit process */
	NULL,                          /* exit master */
	NGX_MODULE_V1_PADDING
};

static ngx_int_t 
ngx_http_php_init(ngx_conf_t *cf)
{
	ngx_http_core_main_conf_t *cmcf;
	ngx_http_php_main_conf_t *pmcf;

	cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);
	pmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_php_module);

	ngx_php_request = NULL;

	if (ngx_http_php_handler_init(cmcf, pmcf) != NGX_OK){
		return NGX_ERROR;
	}

	return NGX_OK;
}

static ngx_int_t 
ngx_http_php_handler_init(ngx_http_core_main_conf_t *cmcf, ngx_http_php_main_conf_t *pmcf)
{
	ngx_int_t i;
	ngx_http_handler_pt *h;
	ngx_http_phases phase;
	ngx_http_phases phases[] = {
		NGX_HTTP_REWRITE_PHASE,
		NGX_HTTP_ACCESS_PHASE,
		NGX_HTTP_CONTENT_PHASE,
	};
	ngx_int_t phases_c;

	phases_c = sizeof(phases) / sizeof(ngx_http_phases);
	for (i = 0; i < phases_c; i++){
		phase = phases[i];
		switch (phase){
			case NGX_HTTP_REWRITE_PHASE:
				if (pmcf->enabled_rewrite_handler){
					h = ngx_array_push(&cmcf->phases[phase].handlers);
					if (h == NULL){
						return NGX_ERROR;
					}
					*h = ngx_http_php_rewrite_handler;
				}
				break;
			case NGX_HTTP_ACCESS_PHASE:
				if (pmcf->enabled_access_handler){
					h = ngx_array_push(&cmcf->phases[phase].handlers);
					if (h == NULL){
						return NGX_ERROR;
					}
					*h = ngx_http_php_access_handler;
				}
				break;
			case NGX_HTTP_CONTENT_PHASE:
				if (pmcf->enabled_content_handler){
					h = ngx_array_push(&cmcf->phases[phase].handlers);
					if (h == NULL){
						return NGX_ERROR;
					}
					*h = ngx_http_php_content_handler;
				}
				break;
			default:
				break;
		}
	}

	return NGX_OK;
}

static void *
ngx_http_php_create_main_conf(ngx_conf_t *cf)
{
	ngx_http_php_main_conf_t *pmcf;

	pmcf = ngx_pcalloc(cf->pool, sizeof(ngx_http_php_main_conf_t));
	if (pmcf == NULL){
		return NULL;
	}

	pmcf->state = ngx_pcalloc(cf->pool, sizeof(ngx_http_php_state_t));
	if (pmcf->state == NULL){
		return NULL;
	}

	pmcf->state->php_init = 0;
	pmcf->state->php_shutdown = 0;

	pmcf->ini_path.len = 0;
	pmcf->init_code = NGX_CONF_UNSET_PTR;
	pmcf->init_inline_code = NGX_CONF_UNSET_PTR;

	return pmcf;
}

static char *
ngx_http_php_init_main_conf(ngx_conf_t *cf, void *conf)
{
	return NGX_CONF_OK;
}

static void *
ngx_http_php_create_loc_conf(ngx_conf_t *cf)
{
	ngx_http_php_loc_conf_t *plcf;

	plcf = ngx_pcalloc(cf->pool, sizeof(ngx_http_php_loc_conf_t));
	if (plcf == NULL){
		return NGX_CONF_ERROR;
	}

	plcf->rewrite_code = NGX_CONF_UNSET_PTR;
	plcf->rewrite_inline_code = NGX_CONF_UNSET_PTR;

	plcf->access_code = NGX_CONF_UNSET_PTR;
	plcf->access_inline_code = NGX_CONF_UNSET_PTR;

	plcf->content_code = NGX_CONF_UNSET_PTR;
	plcf->content_inline_code = NGX_CONF_UNSET_PTR;

	return plcf;
}

static char *
ngx_http_php_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
	ngx_http_php_loc_conf_t *prev = parent;
	ngx_http_php_loc_conf_t *conf = child;

	prev->rewrite_code = conf->rewrite_code;
	prev->rewrite_inline_code = conf->rewrite_inline_code;

	prev->access_code = conf->access_code;
	prev->access_inline_code = conf->access_inline_code;

	prev->content_code = conf->content_code;
	prev->content_inline_code = conf->content_inline_code;

	return NGX_CONF_OK;
}

static ngx_int_t 
ngx_http_php_init_worker(ngx_cycle_t *cycle)
{
	ngx_http_php_main_conf_t *pmcf;

	pmcf = ngx_http_cycle_get_module_main_conf(cycle, ngx_http_php_module);

	php_ngx_module.ub_write = ngx_http_php_code_ub_write;
	php_ngx_module.flush = ngx_http_php_code_flush;
	php_ngx_module.log_message = ngx_http_php_code_log_message;
	php_ngx_module.register_server_variables = ngx_http_php_code_register_server_variables;
	php_ngx_module.read_post = ngx_http_php_code_read_post;
	php_ngx_module.read_cookies = ngx_http_php_code_read_cookies;
	php_ngx_module.header_handler = ngx_http_php_code_header_handler;

	if (pmcf->ini_path.len != 0){
		php_ngx_module.php_ini_path_override = (char *)pmcf->ini_path.data;
	}
	
	php_ngx_module_init(TSRMLS_C);

	old_zend_error_cb = zend_error_cb;
	zend_error_cb = ngx_php_error_cb;

	return NGX_OK;
}

static void 
ngx_http_php_exit_worker(ngx_cycle_t *cycle)
{
	php_ngx_module_shutdown(TSRMLS_C);
}



















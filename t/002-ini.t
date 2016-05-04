# vim:set ft= ts=4 sw=4 et fdm=marker:

use Test::Nginx::Socket 'no_plan';

run_tests();

__DATA__

=== TEST 1: ini file
ini file
--- http_config
php_ini_path /home/travis/build/rryqszq4/ngx_php/build/php/etc/php.ini;
--- config
location = /ini {
    php_content_handler_code '
		echo php_ini_loaded_file();
	';
}
--- request
GET /ini
--- response_body
/home/travis/build/rryqszq4/ngx_php/build/php/etc/php.ini
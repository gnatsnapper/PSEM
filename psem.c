/* psem extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"

#include "zend_exceptions.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#include "php_psem.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

zend_class_entry *psem_ce;
static zend_object_handlers psem_object_handlers;

/* {{{ string psem_info( string $name )
 */
PHP_FUNCTION(psem_info)
{

    zend_string *name;
//    int retval;
//    sem_t *sem;
//    int sval;
    //Perhaps mount the file from dev/shm and get info that way
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(name)
    ZEND_PARSE_PARAMETERS_END();

//    sem = sem_open(ZSTR_VAL(name),O_CREAT);
//    if(sem == SEM_FAILED)
//    {
        zend_throw_exception (zend_ce_exception, "See Docs", 0);
//    }

    //fix this throws sefault
    //retval = sem_getvalue(sem, &sval);
//    retval = 1;

//    if (retval == -1)
//    {
//      zend_throw_exception (zend_ce_exception, strerror (errno), 0);
//    }

//    retval = sem_close (sem);

//    if (retval == -1)
//    {
//      zend_throw_exception (zend_ce_exception, strerror (errno), 0);
//    }

//    array_init (return_value);
//    add_assoc_long (return_value, "value", sval);


}
/* }}}*/

/* {{{ void psem___construct( string $name )
 */
PHP_METHOD(PSEM,__construct)
{
        zend_string *name;
        sem_t *semaphore;
        int oflag = O_CREAT;
        mode_t mode = 0666;
        int value = 1;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();

        if((semaphore = sem_open(ZSTR_VAL(name), oflag, mode, (int)value)) == SEM_FAILED)
        {

        zend_throw_exception(zend_ce_exception, strerror(errno),  0);

        }


	php_psem_initialize(Z_PHPPSEM_P(ZEND_THIS), ZSTR_VAL(name), semaphore);
}
/* }}} */

/* {{{ array PSEM::info(  )
 */
PHP_METHOD(PSEM,info)
{
     php_psem_obj *psemobj;
     int retval,sval;

     ZEND_PARSE_PARAMETERS_NONE();

     psemobj = Z_PHPPSEM_P(getThis());

     retval = sem_getvalue(psemobj->semaphore,&sval);
     if (retval == -1)
     {

        zend_throw_exception(zend_ce_exception, strerror(errno),  0);

     }

     array_init (return_value);
     add_assoc_long (return_value, "value", sval);

}
/* }}}*/

/* {{{ bool PSEM::unlink(  )
 */
PHP_METHOD(PSEM,unlink)
{
     php_psem_obj *psemobj;
     int retval;

     ZEND_PARSE_PARAMETERS_NONE();

     psemobj = Z_PHPPSEM_P(getThis());

     sem_unlink(psemobj->name);
     if (retval == -1)
     {

        zend_throw_exception(zend_ce_exception, strerror(errno),  0);

     }

     RETURN_TRUE;

}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(psem)
{
#if defined(ZTS) && defined(COMPILE_DL_PSEM)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(psem)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "psem support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_psem_info, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_psem_class_construct, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_psem_class_info, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_psem_class_unlink, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ psem_functions[]
 */
static const zend_function_entry psem_functions[] = {
	PHP_FE(psem_info,		arginfo_psem_info)
	PHP_FE_END
};
/* }}} */

/* {{{ psem_methods[]
 */
static const zend_function_entry psem_methods[] = {
	PHP_ME(PSEM, __construct,	arginfo_psem_class_construct, ZEND_ACC_PUBLIC)
	PHP_ME(PSEM, info,      arginfo_psem_class_info, ZEND_ACC_PUBLIC)
	PHP_ME(PSEM, unlink,    arginfo_psem_class_unlink, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/* {{{ psem_module_entry
 */
zend_module_entry psem_module_entry = {
	STANDARD_MODULE_HEADER,
	"psem",	/* Extension name */
        psem_functions,			/* zend_function_entry */
	PHP_MINIT(psem),			/* PHP_MINIT - Module initialization */
	NULL,					/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(psem),			/* PHP_RINIT - Request initialization */
	NULL,					/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(psem),			/* PHP_MINFO - Module info */
	PHP_PSEM_VERSION,/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PSEM
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(psem)
#endif

/* {{{ PHP_MINIT_FUNCTION(psem)
 */
PHP_MINIT_FUNCTION(psem)
{
        zend_class_entry ce_psem;

        INIT_CLASS_ENTRY(ce_psem, "PSEM", psem_methods);
	ce_psem.create_object = psem_object_init;
	psem_ce = zend_register_internal_class_ex(&ce_psem, NULL);
	memcpy(&psem_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
//	psem_object_handlers_psem.offset = XtOffsetOf(php_psem_obj, std);
//	psem_object_handlers_psem.free_obj = psem_object_free_storage;
//	psem_object_handlers_psem.clone_obj = psem_object_clone;
//	psem_object_handlers_psem.dtor_obj = psem_object_destroy;
//	psem_object_handlers_psem.compare_objects = psem_object_compare;
//	psem_object_handlers_psem.get_properties_for = psem_object_get_properties_for;
//	psem_object_handlers_psem.get_gc = psem_object_get_gc;

	return SUCCESS;

}
/* }}} */

/* {{{ psem_object_init(ce)
 */
static zend_object *psem_object_init(zend_class_entry *ce) /* {{{ */
{
	php_psem_obj *intern = zend_object_alloc(sizeof(php_psem_obj), ce);

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);
	intern->std.handlers = &psem_object_handlers;

	return &intern->std;
}
/* }}} */


/* {{{ php_psem_initialize(*psemobj, *name)
 */
PHPAPI int php_psem_initialize(php_psem_obj *psemobj, /*const*/ char *name, sem_t *semaphore)
{
        psemobj->name = name;
        psemobj->semaphore = semaphore;

	return 1;
}
/* }}} */


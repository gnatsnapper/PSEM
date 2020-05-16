/* psem extension for PHP */

#ifndef PHP_PSEM_H
# define PHP_PSEM_H

extern zend_module_entry psem_module_entry;
# define phpext_psem_ptr &psem_module_entry

# define PHP_PSEM_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_PSEM)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

PHP_FUNCTION(psem_info);
PHP_METHOD(PSEM, __construct);
PHP_METHOD(PSEM, info);
PHP_METHOD(PSEM, unlink);

PHP_RINIT_FUNCTION(psem);
PHP_RSHUTDOWN_FUNCTION(psem);
PHP_MINIT_FUNCTION(psem);
PHP_MSHUTDOWN_FUNCTION(psem);
PHP_MINFO_FUNCTION(psem);

typedef struct _php_psem_obj php_psem_obj;

struct _php_psem_obj {
        char *name;
        sem_t *semaphore;
	zend_object   std;
};

static zend_object *psem_object_init(zend_class_entry *class_type);
PHPAPI int php_psem_initialize(php_psem_obj *psemobj, char *name, sem_t *semaphore);
static inline php_psem_obj *php_psem_obj_from_obj(zend_object *obj) {
	return (php_psem_obj*)((char*)(obj) - XtOffsetOf(php_psem_obj, std));
}

#define Z_PHPPSEM_P(zv)  php_psem_obj_from_obj(Z_OBJ_P((zv)))

#endif	/* PHP_PSEM_H */

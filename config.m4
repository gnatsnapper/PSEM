dnl config.m4 for extension psem

PHP_ARG_ENABLE(psem, whether to enable psem support,
dnl Make sure that the comment is aligned:
[  --enable-psem          Enable psem support], no)

PHP_ARG_ENABLE([psem],
  [whether to enable psem support],
  [AS_HELP_STRING([--enable-psem],
    [Enable psem support])],
  [no])

dnl if test "$PHP_PSHM" != "no"; then
  AC_DEFINE(HAVE_PSHM, 1, [ Have psem support ])

    LDFLAGS="$LDFLAGS -lrt -lpthread"

  PHP_NEW_EXTENSION(psem, psem.c, $ext_shared)
dnl fi

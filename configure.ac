#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

CC_PREREQ(2.53)
AC_INIT(robs, 0.0.1, liesch@gmx.ch)
AC_CONFIG_AUX_DIR([config])
AM_CONFIG_HEADER([config/config.h])

dnl This is a Hack to deal with a Macro name descrpency between Autoconf
dnl Versions. 
m4_ifdef([AC_INIT_AUTOMAKE], [AC_INIT_AUTOMAKE]) dnl 2.53
m4_ifdef([AM_INIT_AUTOMAKE], [AM_INIT_AUTOMAKE]) dnl 2.57

# Setting up C compiler stuff 
AC_PROG_CXX
AC_PROG_CPP
AC_AIX
AC_ISC_POSIX
AC_HEADER_STDC
AC_CHECK_HEADERS([unistd.h])
AC_PROG_LIBTOOL
AC_CONFIG_MACRO_DIR([m4])

# Checks for typedefs, structures, and compiler characteristics.
dnl 2.53 also doesn't have this
m4_ifdef([AC_HEADER_STDBOOL], [AC_HEADER_STDBOOL])
AC_C_CONST
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_SELECT_ARGTYPES
AC_CHECK_FUNCS([bzero select socket])

# customize settings

# Store settings for includes, libs and flags
INCLUDES="-I/usr/include/bullet"
CPPFLAGS="$CFLAGS $INCLUDES"
LIBS="-lGL -lGLU -lglut"

# generate makefiles
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT


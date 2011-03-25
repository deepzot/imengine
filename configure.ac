#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([imengine], [0.6])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([imengine.h])
AC_CONFIG_HEADERS([config.h])

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt getrusage])

# Checks for programs.
AC_PROG_CXX
AC_PROG_RANLIB

# Checks for header files.

# Checks for libraries.
AC_CHECK_LIB([boost_program_options], [main], ,
             AC_MSG_ERROR([You need libboost-program-options-dev]))
AC_CHECK_LIB([z], [main], ,
             AC_MSG_ERROR([You need libzip-dev]))
AC_CHECK_LIB([png12], [main], ,
             AC_MSG_ERROR([You need libpngXX-dev]))
AC_CHECK_LIB([gslcblas], [main], ,
             AC_MSG_ERROR([You need libgsl0-dev]))
AC_CHECK_LIB([gsl], [main], ,
             AC_MSG_ERROR([You need libgsl0-dev]))
AC_CHECK_LIB([fftw3], [main], ,
             AC_MSG_ERROR([You need libfftw3-dev]))

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

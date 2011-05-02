#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([imengine], [0.9])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([imengine/imengine.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_RANLIB

# Checks for header files.

# Check for the GNU Scientific Library (GSL)
# See http://www.gnu.org/software/gsl/manual/html_node/Autoconf-Macros.html
AC_CHECK_LIB([m],[cos], ,
	AC_MSG_ERROR([No math library installed.]))
AC_CHECK_LIB([gslcblas],[cblas_dgemm], ,
	AC_MSG_ERROR([No GSL CBLAS library installed.]))
AC_CHECK_LIB([gsl],[gsl_blas_dgemm], ,
	AC_MSG_ERROR([No GSL library installed.]))

# Checks for libraries.
# FIXME: Replace `main' with a function in each library:
AC_CHECK_LIB([boost_program_options], [main], ,
             AC_MSG_ERROR([You need libboost-program-options-dev]))
AC_CHECK_LIB([z], [main], ,
             AC_MSG_ERROR([You need libzip-dev]))
AC_CHECK_LIB([png], [main], ,
             AC_MSG_ERROR([You need libpngXX-dev]))
AC_CHECK_LIB([fftw3], [main], ,
             AC_MSG_ERROR([You need libfftw3-dev]))

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt getrusage])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

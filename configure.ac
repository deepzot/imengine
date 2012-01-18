#################################################################################
## Run autoreconf after making any change here.
## Created by David Kirkby <dkirkby@uci.edu>
#################################################################################

# This could probably be relaxed to an older version.
AC_PREREQ([2.68])

# Our package info.
AC_INIT([imengine], [1.0], [dkirkby@uci.edu])

# Checks for programs
AC_PROG_CXX

# Initialize libtool, which adds --enable/disable-shared configure options.
# The boost.m4 macros used below also need this.
LT_INIT

## Checks for libraries:
# GNU Scientific Library (GSL)
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
             AC_MSG_ERROR([You need libboost-program-options]))
AC_CHECK_LIB([z], [main], ,
             AC_MSG_ERROR([You need libzip]))
AC_CHECK_LIB([png], [main], ,
             AC_MSG_ERROR([You need libpng]))
AC_CHECK_LIB([fftw3], [main], ,
             AC_MSG_ERROR([You need libfftw3]))

# Configure automake
AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# See http://www.gnu.org/s/hello/manual/automake/maintainer_002dmode.html
AM_MAINTAINER_MODE

AC_OUTPUT

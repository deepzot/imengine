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

# We need a recent version of boost
BOOST_REQUIRE([1.45])

## Checks for libraries:
# GNU Scientific Library (GSL)
# See http://www.gnu.org/software/gsl/manual/html_node/Autoconf-Macros.html
AC_CHECK_LIB([m],[cos], ,
	AC_MSG_ERROR([No math library installed.]))
AC_CHECK_LIB([gsl],[gsl_sf_gamma], ,
	AC_MSG_ERROR([No GSL library installed.]))
AC_CHECK_LIB([fftw3], [main], ,
	AC_MSG_ERROR([You need libfftw3]))

# Following http://www.gentoo.org/proj/en/qa/automagic.xml below...

# Use 'configure --without-png' if PNG output is not needed (or libz and libpng are not available)
AC_ARG_WITH([png],
	AS_HELP_STRING([--without-png], [Build without PNG output.]))
AS_IF([test "x$with_png" != "xno"], [
	AC_CHECK_LIB([png],[main],,
		AC_MSG_ERROR([You need libpng.]))
])
AS_IF([test "x$with_png" != "xno"], [
	AC_CHECK_LIB([z],[main],,
		AC_MSG_ERROR([You need libz.]))
])

# Configure automake
AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# See http://www.gnu.org/s/hello/manual/automake/maintainer_002dmode.html
AM_MAINTAINER_MODE
AC_CONFIG_HEADERS([config.h])

# Define automake variables that flag whether optional libraries should be used.
AM_CONDITIONAL([USE_PNG], [test "x$ac_cv_lib_png_main" = "xyes"])

AC_OUTPUT

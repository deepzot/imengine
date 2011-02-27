// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_FFTW
#define IMENGINE_FFTW

// Declares our compile-time interface to the FFTW3 library

/*
Use the following configuration options to build each version of the fftw3 library:

 - float(libfftw3f): configure --enable-sse --enable-float
 - long double(libfftw3l): configure --enable-long-double
 - double(libfftw3): configure --enable-sse2

In order to change the precision of the FFTW transforms, using the following steps:

 - modify the Real typedef in types.h
 - select the appropriate FFTW(X) definition below
 - select the appropriate FFTW3LIB definition in Makefile

*/

#include "fftw3.h"

#define FFTW(X) fftw_ ## X // double transforms
//#define FFTW(X) fftwf_ ## X // float transforms
//#define FFTW(X) fftwl_ ## X // long double transforms

#endif // IMENGINE_FFTW
// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_FFTW
#define IMENGINE_FFTW

// Declares our compile-time interface to the FFTW3 library

#include "fftw3.h"

#define FFTW(X) fftw_ ## X // double transforms
//#define FFTW(X) fftwf_ ## X // float transforms
//#define FFTW(X) fftwl_ ## X // long double transforms

#endif // IMENGINE_FFTW
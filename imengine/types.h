// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_TYPES
#define IMENGINE_TYPES

namespace imengine {

    // Defines the representation of real and complex discrete Fourier transform data.
    // See the notes in fftw.h about changing the Real type.
    
    typedef double Real;
    typedef Real Complex[2];  // [0]=re, [1]=im

} // imengine

#endif // IMENGINE_TYPES
// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_FAST_TRANSFORM
#define IMENGINE_FAST_TRANSFORM

#include "imengine/TransformData.h"

#include "fftw3.h"

namespace imengine {
	class FastTransform : public TransformData {
	public:
	    // Implements discrete Fourier transforms using the optimized FFTW library
		FastTransform(InterpolationData &target);
		virtual ~FastTransform();
        // Sets our contents to the discrete Fourier transform of our target InterpolationData
        // object. Normalization is defined by:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void setToTransform();
        // Calculates the real part of our inverse Fourier transform and saves the result
        // in our target InterpolationData object. Normalization is defined by:
        // data[m,n] = 1/N^2 Re[Sum[transform[j,k] Exp[+2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]]
        virtual void inverseTransform();
	private:
        fftw_plan _forwardPlan, _inversePlan;
	}; // FastTransform
} // imengine

#endif // IMENGINE_FAST_TRANSFORM

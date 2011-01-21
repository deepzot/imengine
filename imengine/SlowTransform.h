// Created 19-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_SLOW_TRANSFORM
#define IMENGINE_SLOW_TRANSFORM

#include "imengine/TransformData.h"

namespace imengine {
	class SlowTransform : public TransformData {
	public:
	    // Implements discrete Fourier transforms using explicit summation formulas
		SlowTransform(InterpolationData &target);
		virtual ~SlowTransform();
        // Sets our contents to the discrete Fourier transform of our target InterpolationData
        // object. Normalization is defined by:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void setToTransform();
        // Calculates the real part of our inverse Fourier transform and saves the result
        // in our target InterpolationData object. Normalization is defined by:
        // data[m,n] = 1/N^2 Re[Sum[transform[j,k] Exp[+2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]]
        virtual void inverseTransform();
	private:
	}; // SlowTransform
} // imengine

#endif // IMENGINE_SLOW_TRANSFORM

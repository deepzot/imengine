// Created 19-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_SLOW_TRANSFORM
#define IMENGINE_SLOW_TRANSFORM

#include "imengine/TransformData.h"

#include "imengine/ptr_types.h"

namespace imengine {
	class SlowTransform : public TransformData {
	public:
	    // Implements discrete Fourier transforms using explicit summation formulas
		SlowTransform(InterpolationDataPtr target);
		virtual ~SlowTransform();
        // Sets our contents to the discrete Fourier transform of our target
        // InterpolationData object. Normalization is defined by:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void setToTransform();
        // Calculates the real part of our inverse Fourier transform and saves the result
        // in our target InterpolationData object. Normalization is defined by:
        // data[m,n] = Re[Sum[transform[j,k] Exp[+2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]]
        virtual void inverseTransform();
        // Returns a smart pointer to a new object that shares our target but does
        // not copy our transform data.
        virtual TransformDataPtr clone() const;
	private:
	}; // SlowTransform
} // imengine

#endif // IMENGINE_SLOW_TRANSFORM

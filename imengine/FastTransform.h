// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_FAST_TRANSFORM
#define IMENGINE_FAST_TRANSFORM

#include "imengine/TransformData.h"

namespace imengine {
	class FastTransform : public TransformData {
	public:
	    // Implements discrete Fourier transforms using the optimized FFTW library
		FastTransform(boost::shared_ptr<InterpolationData> target);
		virtual ~FastTransform();
        // Sets our contents to the discrete Fourier transform of our target InterpolationData
        // object. Normalization is defined by:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void setToTransform();
        // Calculates the real part of our inverse Fourier transform and saves the result
        // in our target InterpolationData object. Normalization is defined by:
        // data[m,n] = Re[Sum[transform[j,k] Exp[+2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]]
        virtual void inverseTransform();
        // Returns a smart pointer to a new object that has the same properties as
        // this one. The data from this object is not copied into the new object.
        virtual TransformDataPtr clone() const;
	private:
        // These really have type FFTW(plan) but we are hiding this here so that other
        // packages using our public API will not need to include FFTW headers.
        void *_forwardPlan, *_inversePlan;
	}; // FastTransform
} // imengine

#endif // IMENGINE_FAST_TRANSFORM

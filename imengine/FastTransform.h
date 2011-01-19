// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_FAST_TRANSFORM
#define IMENGINE_FAST_TRANSFORM

#include "imengine/TransformData.h"

namespace imengine {
	class FastTransform : public TransformData {
	public:
	    // Implements discrete Fourier transforms using the optimized FFTW library
		FastTransform(int gridSize, double gridSpacing);
		virtual ~FastTransform();
		// Creates a new transform data object for the specified target
		static FastTransform *createForTarget(InterpolationData& target);
        // Sets our contents to the discrete Fourier transform of the specified row-wise
        // real 2D data array, normalized so that:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void setToTransform(double const *realData);
        // Calculates the real part of our inverse Fourier transform and saves the result
        // in the storage provided. Normalization is defined by:
        // data[m,n] = 1/N^2 Re[Sum[transform[j,k] Exp[+2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]]
        virtual void inverseTransform(InterpolationData &result) const;
	private:
	}; // FastTransform
} // imengine

#endif // IMENGINE_FAST_TRANSFORM

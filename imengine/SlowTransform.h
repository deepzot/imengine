// Created 19-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_SLOW_TRANSFORM
#define IMENGINE_SLOW_TRANSFORM

#include "imengine/TransformData.h"

namespace imengine {
	class SlowTransform : public TransformData {
	public:
	    // Implements discrete Fourier transforms using explicit summation formulas
		SlowTransform(int gridSize, double gridSpacing);
		virtual ~SlowTransform();
		// Creates a new transform data object for the specified target
		static SlowTransform *createForTarget(InterpolationData& target);
        // Sets our contents to the discrete Fourier transform of the specified row-wise
        // real 2D data array, normalized so that:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void setToTransform(double const *realData);
        // Calculates the real part of our inverse Fourier transform and saves the result
        // in the storage provided. Normalization is defined by:
        // data[m,n] = 1/N^2 Re[Sum[transform[j,k] Exp[+2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]]
        virtual void inverseTransform(InterpolationData &result) const;
	private:
	}; // SlowTransform
} // imengine

#endif // IMENGINE_SLOW_TRANSFORM

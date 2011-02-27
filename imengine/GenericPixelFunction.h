// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_GENERIC_PIXEL_FUNCTION
#define IMENGINE_GENERIC_PIXEL_FUNCTION

#include "imengine/AbsPixelFunction.h"

namespace imengine {
	class GenericPixelFunction : public AbsPixelFunction {
	public:
		GenericPixelFunction();
		virtual ~GenericPixelFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const = 0;
        // Computes the function's discrete Fourier transform and saves the results in
        // the transform object passed to initTransform(). The transform is defined as:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void doTransform();
	private:
	}; // GenericPixelFunction
} // imengine

#endif // IMENGINE_GENERIC_PIXEL_FUNCTION

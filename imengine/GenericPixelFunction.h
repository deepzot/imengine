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
        // Performs one-time initializations before subsequent calls to doTransform.
        virtual void initTransform(TransformData *transformData);
        // Computes the function's discrete Fourier transform on a square grid with
        // the specified spacing and (x,y) origin relative to the grid center. The
        // transform is defined as:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void doTransform(double dx = 0, double dy = 0) const;
	private:
        TransformData *_transformData;
        double *_data;
	}; // GenericPixelFunction
} // imengine

#endif // IMENGINE_GENERIC_PIXEL_FUNCTION

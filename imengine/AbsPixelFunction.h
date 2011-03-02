// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ABS_PIXEL_FUNCTION
#define IMENGINE_ABS_PIXEL_FUNCTION

#include "boost/smart_ptr.hpp"

namespace imengine {
    class TransformData;
    // Declares the abstract interface for a real-valued function on a 2D pixel space.
	class AbsPixelFunction {
	public:
		AbsPixelFunction();
		virtual ~AbsPixelFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const = 0;
        // Performs one-time initializations before subsequent calls to doTransform.
        virtual void initTransform(boost::shared_ptr<TransformData> transformData);
        // Computes the function's discrete Fourier transform and saves the results in
        // the specified transform object. The transform is defined as:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void doTransform(boost::shared_ptr<TransformData> transformData) = 0;
	}; // AbsPixelFunction
} // imengine

#endif // IMENGINE_ABS_PIXEL_FUNCTION

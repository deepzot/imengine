// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ABS_PIXEL_FUNCTION
#define IMENGINE_ABS_PIXEL_FUNCTION

#include "imengine/ptr_types.h"

#include "boost/utility.hpp"

namespace imengine {
    class TransformData;
    // Declares the abstract interface for a real-valued function on a 2D pixel space.
	class AbsPixelFunction : boost::noncopyable {
	public:
		AbsPixelFunction();
		virtual ~AbsPixelFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const = 0;
        // Performs one-time initializations before subsequent calls to doTransform.
        virtual void initTransform(TransformDataPtr transformData);
        // Computes the function's discrete Fourier transform and saves the results in
        // the specified transform object. The transform is defined as:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        void computeTransform(TransformDataPtr transformData);
        // Returns true if the next call to computeTransform() would calculate a different
        // result than the previous call.
        virtual bool hasChanged() const;
    protected:
        // Does the actual work of computeTransform.
        virtual void doTransform(TransformDataPtr transformData) = 0;
        // Registers that our internal state has changed so that the next call to
        // doTransform() would calculate a different result than the previous call.
        void setChanged();
        // Allow subclasses to delegate observing duties by sharing our observer.
        ObserverPtr getObserver() const;
    private:
        ObserverPtr _observer;
	}; // AbsPixelFunction
	
} // imengine

#endif // IMENGINE_ABS_PIXEL_FUNCTION

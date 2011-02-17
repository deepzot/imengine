// Created 17-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_DELTA_FUNCTION
#define IMENGINE_MODELS_DELTA_FUNCTION

#include "imengine/AbsPixelFunction.h"

namespace imengine {
namespace models {
	class DeltaFunction : public AbsPixelFunction {
	public:
		DeltaFunction();
		virtual ~DeltaFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const = 0;
        // Performs one-time initializations before subsequent calls to doTransform.
        // Implementation should save the pointer but does not own it.
        virtual void initTransform(TransformData *transformData) = 0;
        // Computes the function's discrete Fourier transform and saves the results in
        // the transform object passed to initTransform(). The transform is defined as:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void doTransform() = 0;
	private:
        TransformData *_transformData;
	}; // DeltaFunction
}} // imengine::models

#endif // IMENGINE_MODELS_DELTA_FUNCTION

// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_TRANSFORMED_PROFILE_FUNCTION
#define IMENGINE_TRANSFORMED_PROFILE_FUNCTION

#include "imengine/AbsPixelFunction.h"
#include "imengine/TransformData.h"

namespace imengine {
    class AbsRadialProfile;
    class AbsCoordTransform;
	class TransformedProfileFunction : public AbsPixelFunction {
	public:
		TransformedProfileFunction(AbsRadialProfile const &profile, AbsCoordTransform &transform);
		virtual ~TransformedProfileFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const = 0;
        // Performs one-time initializations before subsequent calls to doTransform.
        // Implementation should save the pointer but does not own it.
        virtual void initTransform(TransformData *transformData) = 0;
        // Computes the function's discrete Fourier transform and saves the results in
        // the transform object passed to initTransform(). The transform is defined as:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void doTransform() = 0;
        
        void tabulator(double kx, double ky, TransformData::Complex& value);
	private:
        AbsRadialProfile const &_radialProfile;
        AbsCoordTransform const &_coordTransform;
        TransformData *_transformData;
	}; // TransformedProfileFunction
} // imengine

#endif // IMENGINE_TRANSFORMED_PROFILE_FUNCTION

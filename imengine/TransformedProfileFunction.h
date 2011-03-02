// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_TRANSFORMED_PROFILE_FUNCTION
#define IMENGINE_TRANSFORMED_PROFILE_FUNCTION

#include "imengine/AbsPixelFunction.h"
#include "imengine/types.h"
#include "imengine/ptr_types.h"

namespace imengine {
	class TransformedProfileFunction : public AbsPixelFunction {
	public:
		TransformedProfileFunction(AbsRadialProfilePtr profile, AbsCoordTransformPtr transform);
		virtual ~TransformedProfileFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const;
        // Computes the function's discrete Fourier transform and saves the results in
        // the specified transform object. The transform is defined as:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void doTransform(TransformDataPtr transformData);
        // Tabulates values of our DFT
        void tabulator(double kx, double ky, Complex& value);
	private:
        AbsRadialProfilePtr _radialProfile;
        AbsCoordTransformPtr _coordTransform;
	}; // TransformedProfileFunction
} // imengine

#endif // IMENGINE_TRANSFORMED_PROFILE_FUNCTION

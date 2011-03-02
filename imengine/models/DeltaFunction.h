// Created 17-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_DELTA_FUNCTION
#define IMENGINE_MODELS_DELTA_FUNCTION

#include "imengine/AbsPixelFunction.h"
#include "imengine/types.h"

namespace imengine {
namespace models {
	class DeltaFunction : public AbsPixelFunction {
	public:
		DeltaFunction();
		virtual ~DeltaFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const;
        // Computes the function's discrete Fourier transform and saves the results in
        // the specified transform object. The transform is defined as:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void doTransform(boost::shared_ptr<TransformData> transformData);
       // Helper function that initializes our k-space transform
        static void setValueToOne(double kx, double ky, Complex& value);
	private:
	}; // DeltaFunction
}} // imengine::models

#endif // IMENGINE_MODELS_DELTA_FUNCTION

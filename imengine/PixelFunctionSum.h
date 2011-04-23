// Created 22-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_PIXEL_FUNCTION_SUM
#define IMENGINE_PIXEL_FUNCTION_SUM

#include "imengine/AbsPixelFunction.h"

#include "imengine/ptr_types.h"

namespace imengine {
	class PixelFunctionSum : public AbsPixelFunction {
	public:
	    // Creates a pixel function frac1*f1 + (1-frac1)*f2
		PixelFunctionSum(AbsPixelFunctionPtr f1, AbsPixelFunctionPtr f2, double frac1);
		virtual ~PixelFunctionSum();
		// Returns the function value
        virtual double operator()(double x, double y) const;
        // Performs one-time initializations before subsequent calls to doTransform.
        virtual void initTransform(TransformDataPtr transformData);
        // Sets our model parameters
        void setParameters(double frac1);
        // Returns true if the next call to computeTransform() would calculate a different
        // result than the previous call.
        virtual bool hasChanged() const;
    protected:
        // Does the actual work of computeTransform.
        virtual void doTransform(TransformDataPtr transformData);
	private:
        AbsPixelFunctionPtr _f1, _f2;
        TransformDataPtr _transform1, _transform2;
        double _frac1;
	}; // PixelFunctionSum
} // imengine

#endif // IMENGINE_PIXEL_FUNCTION_SUM

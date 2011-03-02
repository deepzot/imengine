// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_TRANSFORMED_PROFILE_FUNCTION
#define IMENGINE_TRANSFORMED_PROFILE_FUNCTION

#include "imengine/AbsPixelFunction.h"
#include "imengine/types.h"

#include "boost/smart_ptr.hpp"

namespace imengine {
    class AbsRadialProfile;
    class AbsCoordTransform;
	class TransformedProfileFunction : public AbsPixelFunction {
	public:
		TransformedProfileFunction(
		    boost::shared_ptr<AbsRadialProfile const> profile,
		    boost::shared_ptr<AbsCoordTransform const> transform);
		virtual ~TransformedProfileFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const;
        // Computes the function's discrete Fourier transform and saves the results in
        // the specified transform object. The transform is defined as:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void doTransform(boost::shared_ptr<TransformData> transformData);
        // Tabulates values of our DFT
        void tabulator(double kx, double ky, Complex& value);
	private:
        boost::shared_ptr<AbsRadialProfile const> _radialProfile;
        boost::shared_ptr<AbsCoordTransform const> _coordTransform;
	}; // TransformedProfileFunction
} // imengine

#endif // IMENGINE_TRANSFORMED_PROFILE_FUNCTION

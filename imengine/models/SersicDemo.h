// Created 17-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_SERSIC_DEMO
#define IMENGINE_MODELS_SERSIC_DEMO

#include "imengine/GenericPixelFunction.h"
#include "imengine/EllipticityTransform.h"

namespace imengine {
namespace models {
	class SersicDemo : public GenericPixelFunction {
	public:
	    // Creates a new model with half-light radius re using the
	    // specified Sersic index and ellipticity parameters.
		SersicDemo(double re, double index, double e1, double e2, double rmax);
		virtual ~SersicDemo();
		virtual double operator()(double x, double y) const;
        // Sets the parameter values to use.
        void setParameters(double re, double index, double e1, double e2, double rmax);
        // Calculate the value of k for the specified index so that re is
        // the half-light radius.
        static double kValue(double index);
	private:
        static double kValueF(double index, void *params);
        static double kValueDF(double index, void *params);
        static void kValueFDF(double index, void *params, double *y, double *dy);
        bool _initialized;
        double _twopi, _re, _alpha, _index, _norm, _inverseIndex, _rmax;
        EllipticityTransform _transform;
	}; // SersicDemo
}} // imengine::models

#endif // IMENGINE_MODELS_SERSIC_DEMO

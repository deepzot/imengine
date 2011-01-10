// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_GAUSSIAN_DEMO
#define IMENGINE_MODELS_GAUSSIAN_DEMO

#include "imengine/GenericPixelFunction.h"

namespace imengine {
namespace models {
	class GaussianDemo : public GenericPixelFunction {
	public:
		GaussianDemo(double sigma);
		virtual ~GaussianDemo();
		// Returns the function value
        virtual double operator()(double x, double y) const;
	private:
        double _sigma,_twosigmasq,_norm;
	}; // GaussianDemo
}} // imengine::models

#endif // IMENGINE_MODELS_GAUSSIAN_DEMO

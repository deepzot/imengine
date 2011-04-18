// Created 17-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_SERSIC_DEMO
#define IMENGINE_MODELS_SERSIC_DEMO

#include "imengine/GenericPixelFunction.h"

namespace imengine {
namespace models {
	class SersicDemo : public GenericPixelFunction {
	public:
		SersicDemo(double alpha, double index);
		virtual ~SersicDemo();
		virtual double operator()(double x, double y) const;
	private:
        double _alpha, _index, _norm;
	}; // SersicDemo
}} // imengine::models

#endif // IMENGINE_MODELS_SERSIC_DEMO

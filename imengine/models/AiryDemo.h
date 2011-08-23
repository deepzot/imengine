// Created 22-Aug-2011 by Daniel Margala (University of California, Irvine) <dmargala@uci.edu>

#ifndef IMENGINE_MODELS_AIRY_DEMO
#define IMENGINE_MODELS_AIRY_DEMO

#include "imengine/GenericPixelFunction.h"
#include "imengine/PolarEllipticityTransform.h"

namespace imengine {
namespace models {
	class AiryDemo : public GenericPixelFunction {
	public:
		static const double AiryConst = 1.2031469076667856695;
		static const double NormConst = 6.8935827897949198235;
		// Creates an Airy model with specified fwhm and ellipticity parameters.
		AiryDemo(double fwhm, double e1, double e2);
		virtual ~AiryDemo();
		// Returns the function value
        virtual double operator()(double x, double y) const;
         // Sets the parameter values to use.
        void setParameters(double fwhm, double e1, double e2);
	private:
		double sinc(const double x) const;
        double _fwhm, _rd, _norm, _e1, _e2;
        bool _initialized;
        PolarEllipticityTransform _transform;
	}; // AiryDemo
}} // imengine::models

#endif // IMENGINE_MODELS_AIRY_DEMO

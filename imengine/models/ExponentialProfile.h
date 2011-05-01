// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_EXPONENTIAL_PROFILE
#define IMENGINE_MODELS_EXPONENTIAL_PROFILE

#include "imengine/AbsRadialProfile.h"

namespace imengine {
namespace models {
	class ExponentialProfile : public imengine::AbsRadialProfile {
	public:
        static const double k = 1.67835;
	    // Represents the normalized radial profile exp(-k*(r/re)) where k = 1.67835 is
	    // fixed and chosen so that half of the intensity is contained within r < re.
		ExponentialProfile(double re);
		virtual ~ExponentialProfile();
		// Evaluates this profile at the specified radius.
        virtual double operator()(double r) const;
        // Evaluates this profile's real-valued radial integral for the specified kappa.
        virtual double radialIntegral(double kappa) const;
        // Sets the parameter values to use.
        void setParameters(double re);
	private:
        double _re,_alpha,_norm,_twopi;
	}; // ExponentialProfile
}} // imengine::models

#endif // IMENGINE_MODELS_EXPONENTIAL_PROFILE

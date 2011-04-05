// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_MOFFAT_PROFILE
#define IMENGINE_MODELS_MOFFAT_PROFILE

#include "imengine/AbsRadialProfile.h"

namespace imengine {
namespace models {
	class MoffatProfile : public imengine::AbsRadialProfile {
	public:
	    // Represents the normalized radial profile (1 + (r/rd)^2)^(-beta) where
	    // rd = fwhm/(2 sqrt(2^(1/beta)-1)) and beta > 1.
		MoffatProfile(double fwhm, double beta);
		virtual ~MoffatProfile();
		// Evaluates this profile at the specified radius.
        virtual double operator()(double r) const;
        // Evaluates this profile's real-valued radial integral for the specified kappa.
        virtual double radialIntegral(double kappa) const;
        // Sets the parameter values to use.
        void setParameters(double fwhm, double beta);
	private:
        double _pi, _fwhm, _beta, _nu, _rd, _norm, _integralNorm;
	}; // MoffatProfile
}} // imengine::models

#endif // IMENGINE_MODELS_MOFFAT_PROFILE

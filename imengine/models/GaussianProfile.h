// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_GAUSSIAN_PROFILE
#define IMENGINE_MODELS_GAUSSIAN_PROFILE

#include "imengine/AbsRadialProfile.h"

namespace imengine {
namespace models {
	class GaussianProfile : public imengine::AbsRadialProfile {
	public:
		GaussianProfile(double sigma);
		virtual ~GaussianProfile();
		// Evaluates this profile at the specified radius.
        virtual double operator()(double r) const;
        // Evaluates this profile's real-valued radial integral for the specified kappa.
        virtual double radialIntegral(double kappa) const;
	private:
        double _twosigsq, _sigsqby2, _norm;
	}; // GaussianProfile
}} // imengine::models

#endif // IMENGINE_MODELS_GAUSSIAN_PROFILE

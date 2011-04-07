// Created 25-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_DISK_PROFILE
#define IMENGINE_MODELS_DISK_PROFILE

#include "imengine/AbsRadialProfile.h"

namespace imengine {
namespace models {
	class DiskProfile : public imengine::AbsRadialProfile {
	public:
		DiskProfile(double radius);
		virtual ~DiskProfile();
		// Evaluates this profile at the specified radius.
        virtual double operator()(double r) const;
        // Evaluates this profile's real-valued radial integral for the specified kappa.
        virtual double radialIntegral(double kappa) const;
        // Sets the parameter values to use.
        void setParameters(double radius);
	private:
        double _radius, _norm, _pi;
	}; // DiskProfile
}} // imengine::models

#endif // IMENGINE_MODELS_DISK_PROFILE

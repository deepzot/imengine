// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ABS_RADIAL_PROFILE
#define IMENGINE_ABS_RADIAL_PROFILE

#include "imengine/ObserverDelegate.h"

namespace imengine {
	class AbsRadialProfile : public ObserverDelegate {
	public:
		AbsRadialProfile();
		virtual ~AbsRadialProfile();
		// Evaluates this profile at the specified radius.
        virtual double operator()(double r) const = 0;
        // Evaluates this profile's real-valued radial integral for the specified kappa.
        virtual double radialIntegral(double kappa) const = 0;
	}; // AbsRadialProfile
} // imengine

#endif // IMENGINE_ABS_RADIAL_PROFILE

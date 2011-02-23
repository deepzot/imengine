// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_IDENTITY_TRANSFORM
#define IMENGINE_IDENTITY_TRANSFORM

#include "imengine/AbsCoordTransform.h"

namespace imengine {
	class IdentityTransform : public AbsCoordTransform {
	public:
		IdentityTransform();
		virtual ~IdentityTransform();
		// Returns the transform determinant
        virtual double determinant() const;
		// Calculates the magnitude |M(x,y)| of the transform of (x,y)
        virtual double transformedRadius(double x, double y) const;
        // Calculates the magnitude |M^(-1)t(kx,ky)| of (kx,ky) transformed by the
        // transpose of the inverse transform
        virtual double transformedWaveNumber(double kx, double ky) const;
	private:
	}; // IdentityTransform
} // imengine

#endif // IMENGINE_IDENTITY_TRANSFORM

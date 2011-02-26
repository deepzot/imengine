// Created 26-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ELLIPTICITY_TRANSFORM
#define IMENGINE_ELLIPTICITY_TRANSFORM

#include "imengine/AbsCoordTransform.h"

namespace imengine {
	class EllipticityTransform : public AbsCoordTransform {
	public:
		EllipticityTransform(double e1, double e2);
		virtual ~EllipticityTransform();
		// Returns the transform determinant
        virtual double determinant() const;
		// Calculates the magnitude |M(x,y)| of the transform of (x,y)
        virtual double transformedRadius(double x, double y) const;
        // Calculates the magnitude |M^(-1)t(kx,ky)| of (kx,ky) transformed by the
        // transpose of the inverse transform
        virtual double transformedWaveNumber(double kx, double ky) const;
	private:
        double _e1m,_e1p,_e2,_detM;
	}; // EllipticityTransform
} // imengine

#endif // IMENGINE_ELLIPTICITY_TRANSFORM

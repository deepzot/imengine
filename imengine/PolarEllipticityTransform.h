// Created 10-May-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_POLAR_ELLIPTICITY_TRANSFORM
#define IMENGINE_POLAR_ELLIPTICITY_TRANSFORM

#include "imengine/AbsCoordTransform.h"

namespace imengine {
	class PolarEllipticityTransform : public AbsCoordTransform {
	public:
	    // Creates a transformation from elliptical (observed) to circular (source)
	    // coordinates using a composition of shear transforms, M(e1,e2) M(g1,g2),
	    // similar to the EllipticityTransform class but using a different
	    // parameterization that is better suited for fitting, where the effects
	    // of (e1,e2) and (g1,g2) are highly correlated:
	    //
	    //  eg1 = e1 + g1
	    //  eg2 = e2 + g2
	    //  egcos = e1 g1 + e2 g2
	    //  egsin = e2 g1 - e1 g2
	    //
	    // Use the defaults egcos = egsin = 0 to model a single shear transformation.
		PolarEllipticityTransform(double eg1, double eg2, double egcos = 0, double egsin = 0);
		virtual ~PolarEllipticityTransform();
		// Returns the transform determinant
        virtual double determinant() const;
		// Calculates the magnitude |M(x,y)| of the transform of (x,y)
        virtual double transformedRadius(double x, double y) const;
        // Calculates the magnitude |M^(-1)t(kx,ky)| of (kx,ky) transformed by the
        // transpose of the inverse transform
        virtual double transformedWaveNumber(double kx, double ky) const;
        // Sets the ellipticity parameter values to use.
        void setParameters(double eg1, double eg2, double egcos = 0, double egsin = 0);
	private:
        double _eg1,_eg2,_egcos,_egsin,_a,_b,_c,_d,_detM;
	}; // EllipticityTransform
} // imengine

#endif // IMENGINE_POLAR_ELLIPTICITY_TRANSFORM

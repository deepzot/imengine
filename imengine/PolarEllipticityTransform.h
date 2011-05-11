// Created 10-May-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_POLAR_ELLIPTICITY_TRANSFORM
#define IMENGINE_POLAR_ELLIPTICITY_TRANSFORM

#include "imengine/AbsCoordTransform.h"

namespace imengine {
	class PolarEllipticityTransform : public AbsCoordTransform {
	public:
	    // Creates a transformation from elliptical (observed) to circular (source)
	    // coordinates using a composition of shear transforms, M(e1,e2) M(g1,g2),
	    // similar to the EllipticityTransform class but using polar coordinate
	    // parameters:
	    //
	    //  e1 + g1 = EG(lambda) cos(2 phi)
	    //  e2 + g2 = EG(lambda) sin(2 phi)
	    //  e1 g1 + e2 g2 = egcos
	    //  e2 g1 - e1 g2 = egsin
	    //
	    // where EG(lambda) = (lambda^2 - 1)/(lambda^2 + 1) with lambda representing
	    // the factor by which the unit vector should be stretched (shrunk) to
	    // obtain the major (minor) axis, so that the major/minor ratio is lambda^2,
	    // and phi is the orientation of the major axis (assuming lambda > 1).
	    // The parameters egcos, egsin correspond to:
	    //
	    //  egcos = |e| |g| cos(dtheta)
	    //  egsin = |e| |g| sin(dtheta)
	    //
	    // where dtheta is the angle between (e1,e2) and (g1,g2) and |e|, |g| are
	    // their magnitudes.
        //
	    // Use the defaults egcos = egsin = 0 to model a single shear transformation.
		PolarEllipticityTransform(double lambda, double phi,
		    double egcos = 0, double egsin = 0);
		virtual ~PolarEllipticityTransform();
		// Returns the transform determinant
        virtual double determinant() const;
		// Calculates the magnitude |M(x,y)| of the transform of (x,y)
        virtual double transformedRadius(double x, double y) const;
        // Calculates the magnitude |M^(-1)t(kx,ky)| of (kx,ky) transformed by the
        // transpose of the inverse transform
        virtual double transformedWaveNumber(double kx, double ky) const;
        // Sets the ellipticity parameter values to use.
        void setParameters(double lambda, double phi, double egcos = 0, double egsin = 0);
	private:
        double _lambda,_phi,_egcos,_egsin,_a,_b,_c,_d,_detM;
	}; // EllipticityTransform
} // imengine

#endif // IMENGINE_POLAR_ELLIPTICITY_TRANSFORM

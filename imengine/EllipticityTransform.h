// Created 26-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ELLIPTICITY_TRANSFORM
#define IMENGINE_ELLIPTICITY_TRANSFORM

#include "imengine/AbsCoordTransform.h"

namespace imengine {
	class EllipticityTransform : public AbsCoordTransform {
	public:
	    // Creates a transformation from elliptical (observed) to circular (source)
	    // coordinates using a composition of shear transforms, M(e1,e2) M(g1,g2),
	    // where M(q1,q2) has components:
	    //
	    //   1-q1   -q2
	    //   -q2   1+q1
	    //
	    // The intended use case is to combine a (small) weak-lensing shear (g1,g2)
	    // with an intrinsic ellipticity (e1,e2). Note that for |g| << |e|,
	    // M(e1,e2) M(g1,g2) is approximately M(e1+g1,e2+g2) but this implementation
	    // is exact and includes the necessary corrections of order |g|/(|e|+|g|).
	    // Use the defaults g1 = g2 = 0 to model a single shear transformation.
		EllipticityTransform(double e1, double e2, double g1 = 0, double g2 = 0);
		virtual ~EllipticityTransform();
		// Returns the transform determinant
        virtual double determinant() const;
		// Calculates the magnitude |M(x,y)| of the transform of (x,y)
        virtual double transformedRadius(double x, double y) const;
        // Calculates the magnitude |M^(-1)t(kx,ky)| of (kx,ky) transformed by the
        // transpose of the inverse transform
        virtual double transformedWaveNumber(double kx, double ky) const;
        // Sets the ellipticity parameter values to use.
        void setParameters(double e1, double e2, double g1 = 0, double g2 = 0);
	private:
        double _e1,_e2,_g1,_g2,_a,_b,_c,_d,_detM;
	}; // EllipticityTransform
} // imengine

#endif // IMENGINE_ELLIPTICITY_TRANSFORM

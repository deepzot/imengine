// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ABS_COORD_TRANSFORM
#define IMENGINE_ABS_COORD_TRANSFORM

namespace imengine {
	class AbsCoordTransform {
	public:
	    // Represents a 2D invertible coordinate transform M
		AbsCoordTransform();
		virtual ~AbsCoordTransform();
		// Returns the transform determinant
        virtual double determinant() const = 0;
		// Calculates the magnitude |M(x,y)| of the transform of (x,y)
        virtual double transformedRadius(double x, double y) const = 0;
        // Calculates the magnitude |M^(-1)t(kx,ky)| of (kx,ky) transformed by the
        // transpose of the inverse transform
        virtual double transformedWaveNumber(double kx, double ky) const = 0;
	private:
	}; // AbsCoordTransform
} // imengine

#endif // IMENGINE_ABS_COORD_TRANSFORM

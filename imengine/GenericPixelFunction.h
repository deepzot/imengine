// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_GENERIC_PIXEL_FUNCTION
#define IMENGINE_GENERIC_PIXEL_FUNCTION

#include "imengine/AbsPixelFunction.h"

namespace imengine {
	class GenericPixelFunction : public AbsPixelFunction {
	public:
		GenericPixelFunction();
		virtual ~GenericPixelFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const = 0;
        // Fills the provided array with the function's discrete Fourier transform on
        // a square ngrid x ngrid lattice with the specified spacing and (x,y) origin
        // relative to the grid center.
        virtual void fillArrayWithTransform(double **array, int ngrid,
            double spacing = 1, double dx = 0, double dy = 0) const = 0;
	private:
	}; // GenericPixelFunction
} // imengine

#endif // IMENGINE_GENERIC_PIXEL_FUNCTION

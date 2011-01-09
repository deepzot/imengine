// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ABS_PIXEL_FUNCTION
#define IMENGINE_ABS_PIXEL_FUNCTION

namespace imengine {
    // Declares the abstract interface for a real-valued function on a 2D pixel space.
	class AbsPixelFunction {
	public:
		AbsPixelFunction();
		virtual ~AbsPixelFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const = 0;
        // Fills the provided array with the function's discrete Fourier transform on
        // a square ngrid x ngrid lattice with the specified spacing and (x,y) origin
        // relative to the grid center.
        virtual void fillArrayWithTransform(double **array, int ngrid,
            double spacing = 1, double dx = 0, double dy = 0) const = 0;
	private:
	}; // AbsPixelFunction
} // imengine

#endif // IMENGINE_ABS_PIXEL_FUNCTION

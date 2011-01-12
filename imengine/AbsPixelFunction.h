// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ABS_PIXEL_FUNCTION
#define IMENGINE_ABS_PIXEL_FUNCTION

namespace imengine {
    class TransformData;
    // Declares the abstract interface for a real-valued function on a 2D pixel space.
	class AbsPixelFunction {
	public:
		AbsPixelFunction();
		virtual ~AbsPixelFunction();
		// Returns the function value
        virtual double operator()(double x, double y) const = 0;
        // Performs one-time initializations before subsequent calls to doTransform.
        // Implementation should save the pointer but does not own it.
        virtual void initTransform(TransformData *transformData) = 0;
        // Computes the function's discrete Fourier transform on a square grid with
        // the specified spacing (x,y) origin relative to the grid center. Returns
        // the overall scale factor necessary so that the result corresponds to:
        // transform[m,n] = 1/N Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual double doTransform(double dx = 0, double dy = 0) const = 0;
	private:
	}; // AbsPixelFunction
} // imengine

#endif // IMENGINE_ABS_PIXEL_FUNCTION

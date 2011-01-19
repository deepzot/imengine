// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_FAST_TRANSFORM_DATA
#define IMENGINE_FAST_TRANSFORM_DATA

#include "imengine/TransformData.h"

namespace imengine {
	class FastTransformData : public TransformData {
	public:
	    // Implements discrete Fourier transforms using the optimized FFTW library
		FastTransformData(int gridSize, double gridSpacing);
		virtual ~FastTransformData();
		// Creates a new transform data object with attributes copied from the specified prototype
		static FastTransformData *createFromPrototype(DataGrid const& prototype);
        // Sets our contents to the discrete Fourier transform of the specified row-wise
        // real 2D data array, normalized so that:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void setToTransform(double const *realData);
	private:
	}; // FastTransformData
} // imengine

#endif // IMENGINE_FAST_TRANSFORM_DATA

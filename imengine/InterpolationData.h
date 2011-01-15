// Created 14-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_INTERPOLATION_DATA
#define IMENGINE_INTERPOLATION_DATA

#include "imengine/DataGrid.h"

namespace imengine {
    // Stores a grid of image function values to support pixelation.
	class InterpolationData : public DataGrid {
	public:
		InterpolationData(int gridSize, int pad, double gridSpacing, double gridX, double gridY);
		virtual ~InterpolationData();
		//
        double offsetValue(double const *ptr, int dx, int dy) const;
	private:
        int _pad;
        double *_data;
	}; // InterpolationData
	
	inline double InterpolationData::offsetValue(double const *ptr, int dx, int dy) const {
        return *(ptr + dy + _gridSize*dx);
	}
} // imengine

#endif // IMENGINE_INTERPOLATION_DATA

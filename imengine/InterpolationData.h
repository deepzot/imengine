// Created 14-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_INTERPOLATION_DATA
#define IMENGINE_INTERPOLATION_DATA

#include "imengine/DataGrid.h"

namespace imengine {
    // Stores a grid of image function values to support pixelation.
	class InterpolationData : public DataGrid {
	public:
		InterpolationData(int gridSize, double gridSpacing, double gridX, double gridY);
		virtual ~InterpolationData();
	private:
	}; // InterpolationData
} // imengine

#endif // IMENGINE_INTERPOLATION_DATA

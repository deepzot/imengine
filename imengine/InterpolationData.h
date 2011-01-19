// Created 14-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_INTERPOLATION_DATA
#define IMENGINE_INTERPOLATION_DATA

#include "imengine/DataGrid.h"

namespace imengine {
    // Stores a grid of image function values to support pixelation.
	class InterpolationData : public DataGrid {
	public:
	    // The reference grid point for pixel (0,0) is at (pad,pad)
		InterpolationData(int gridSize, int pad, double gridSpacing, double gridX, double gridY);
		virtual ~InterpolationData();
		
        // Accesses constructor parameters
        double getGridX() const;
        double getGridY() const;

		// Sets the value associated with grid point (i,j) (no range checks on i,j)
        void setValue(int i, int j, double value);
		
        // Returns the value associated with pixel coord (x,y) (no range checks on x,y)
        double getValueForPixel(int x, int y) const;
        
        // dumps grid values to std::cout in row-wise order
        void dump() const;
        
	private:
        int _pad;
        double _gridX, _gridY;
        double *_data;
	}; // InterpolationData
	
    inline double InterpolationData::getGridX() const { return _gridX; }
    inline double InterpolationData::getGridY() const { return _gridY; }

	inline void InterpolationData::setValue(int i, int j, double value) {
        _data[i + _gridSize*j] = value;
	}
	
	inline double InterpolationData::getValueForPixel(int x, int y) const {
        return _data[getIndex(x + _pad) + _gridSize*getIndex(y + _pad)];
	}
} // imengine

#endif // IMENGINE_INTERPOLATION_DATA

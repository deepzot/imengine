// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_TRANSFORM_DATA
#define IMENGINE_TRANSFORM_DATA

namespace imengine {
    // Stores complex discrete Fourier transform values on a square grid
	class TransformData {
	public:
	    // Creates a new data grid with the specified size and spacing
		TransformData(int gridSize, double gridSpacing);
		virtual ~TransformData();
        inline int getGridSize() const { return _gridSize; }
		// helper functions to access real/imag parts of transform data (no range checks on i,j)
        inline double real(int i, int j) const { return _data[2*(j + _gridSize*i)]; }
        inline double imag(int i, int j) const { return _data[1+2*(j + _gridSize*i)]; }
	private:
        int _gridSize;
        double _gridSpacing;
        double *_data;
	}; // TransformData
} // imengine

#endif // IMENGINE_TRANSFORM_DATA

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
        inline double& real(int i, int j) { return _data[2*(j + _gridSize*i)]; }
        inline double& imag(int i, int j) { return _data[2*(j + _gridSize*i)]; }
        inline const double& real(int i, int j) const { return _data[2*(j + _gridSize*i)]; }
        inline const double& imag(int i, int j) const { return _data[2*(j + _gridSize*i)]; }

        // helper functions to return the wavenumber associated an index value (no range check on i)
        inline double wavenumber(int i) const { return i < _gridSizeBy2 ? i*_dk : (_gridSize-i)*_dk; }

	private:
        int _gridSize,_gridSizeBy2;
        double _gridSpacing, _dk;
        double *_data;
	}; // TransformData
} // imengine

#endif // IMENGINE_TRANSFORM_DATA

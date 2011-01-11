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
		
		// returns read-only initialization attributes
        int getGridSize() const;
        double getGridSpacing() const;

		// accesses the real/imag parts of transform data (no range checks on i,j)
        double& real(int i, int j);
        double& imag(int i, int j);
        double const& real(int i, int j) const;
        double const& imag(int i, int j) const;

        // returns the wavenumber associated an index value (no range check on i)
        double waveNumber(int i) const;
        
        // returns the axis value associated with an index value (no range check on i)
        double axisValue(int i) const;

	private:
        int _gridSize,_break;
        double _gridSpacing, _dk, _dx;
        double *_data;
	}; // TransformData

    inline int TransformData::getGridSize() const { return _gridSize; }
    inline double TransformData::getGridSpacing() const { return _gridSpacing; }

    inline double& TransformData::real(int i, int j) { return _data[2*(j + _gridSize*i)]; }
    inline double& TransformData::imag(int i, int j) { return _data[2*(j + _gridSize*i)]; }
    inline double const& TransformData::real(int i, int j) const { return _data[2*(j + _gridSize*i)]; }
    inline double const& TransformData::imag(int i, int j) const { return _data[2*(j + _gridSize*i)]; }

    inline double TransformData::waveNumber(int i) const {
        return i < _break ? i*_dk : (_gridSize-i)*_dk;
    }

    inline double TransformData::axisValue(int i) const {
        return i < _break ? i*_gridSpacing : (_gridSize-i)*_gridSpacing;
    }

} // imengine

#endif // IMENGINE_TRANSFORM_DATA

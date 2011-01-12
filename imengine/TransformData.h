// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_TRANSFORM_DATA
#define IMENGINE_TRANSFORM_DATA

namespace imengine {
    // Stores complex discrete Fourier transform values on a square grid
	class TransformData {
	public:
	    // Creates a new data grid with the specified size, spacing, and coordinate offset
		TransformData(int gridSize, double gridSpacing, double gridX, double gridY);
		
		// Creates a new data grid with attributes copied from the specified prototype
        static TransformData *createFromPrototype(TransformData const& prototype);
		
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
        
        // returns the axis value associated with an index value (no range check on i,j)
        double getX(int i) const;
        double getY(int j) const;
        
        // fills the specified row-wise 2D data array with the real part of our inverse Fourier transform
        void inverseTransform(double *realData) const;
        
        // Computes the discrete Fourier transform of the specified row-wise real 2D data array
        // Returns the overall scale factor necessary so that the result corresponds to:
        // transform[m,n] = 1/N Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        double setToTransform(double const *realData);
        
        // sets our values to the element-by-element product of two other transforms
        void setToProduct(TransformData const& t1, TransformData const& t2);

	private:
        int _gridSize,_break;
        double _gridSpacing, _gridX, _gridY, _dk, _dx,_norm;
        double *_data;
	}; // TransformData

    inline int TransformData::getGridSize() const { return _gridSize; }
    inline double TransformData::getGridSpacing() const { return _gridSpacing; }

    inline double& TransformData::real(int i, int j) { return _data[2*(j + _gridSize*i)]; }
    inline double& TransformData::imag(int i, int j) { return _data[2*(j + _gridSize*i)+1]; }
    inline double const& TransformData::real(int i, int j) const { return _data[2*(j + _gridSize*i)]; }
    inline double const& TransformData::imag(int i, int j) const { return _data[2*(j + _gridSize*i)+1]; }

    inline double TransformData::waveNumber(int i) const {
        return _dk*(i < _break ? i : i-_gridSize);
    }

    inline double TransformData::getX(int i) const {
        return _gridX + _gridSpacing*(i < _break ? i : i-_gridSize);
    }

    inline double TransformData::getY(int j) const {
        return _gridY + _gridSpacing*(j < _break ? j : j-_gridSize);
    }

} // imengine

#endif // IMENGINE_TRANSFORM_DATA

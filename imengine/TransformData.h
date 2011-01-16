// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_TRANSFORM_DATA
#define IMENGINE_TRANSFORM_DATA

#include "imengine/DataGrid.h"

namespace imengine {
    class InterpolationData;
    // Stores complex discrete Fourier transform values on a square grid
	class TransformData : public DataGrid {
	public:
	    // Creates a new transform data grid with the specified size, spacing, and coordinate offset
		TransformData(int gridSize, double gridSpacing, double gridX, double gridY);		
		virtual ~TransformData();
		
		// Creates a new transform data object with attributes copied from the specified prototype
		static TransformData *createFromPrototype(DataGrid const& prototype, bool preserveOffset);

		// accesses the real/imag parts of transform data (no range checks on i,j)
        double& real(int i, int j);
        double& imag(int i, int j);
        double const& real(int i, int j) const;
        double const& imag(int i, int j) const;
        
        // calculates and returns re*re + im*im (no range checks on i,j)
        double absSquared(int i, int j) const;

        // returns the wavenumber associated an index value (no range check on i)
        double waveNumber(int i) const;
        
        // calculates the real part of our inverse Fourier transform
        void inverseTransform(InterpolationData &result) const;
        
        // Computes the discrete Fourier transform of the specified row-wise real 2D data array
        // Returns the overall scale factor necessary so that the result corresponds to:
        // transform[m,n] = 1/N Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        double setToTransform(double const *realData);
        
        // sets our values to the element-by-element product of two other transforms
        void setToProduct(TransformData const& t1, TransformData const& t2, double norm = 1);
        
        // dumps grid absolute-squared values to std::cout in row-wise order
        void dumpAbsSquared() const;

	private:
        double _dk,_norm;
        double *_data;
	}; // TransformData

    inline double& TransformData::real(int i, int j) { return _data[2*(i + _gridSize*j)]; }
    inline double& TransformData::imag(int i, int j) { return _data[2*(i + _gridSize*j)+1]; }
    inline double const& TransformData::real(int i, int j) const { return _data[2*(i + _gridSize*j)]; }
    inline double const& TransformData::imag(int i, int j) const { return _data[2*(i + _gridSize*j)+1]; }
    
    inline double TransformData::absSquared(int i, int j) const {
        double re(real(i,j)), im(imag(i,j));
        return re*re + im*im;
    }

    inline double TransformData::waveNumber(int i) const {
        return _dk*(i < _break1 ? i : i-_gridSize);
    }

} // imengine

#endif // IMENGINE_TRANSFORM_DATA

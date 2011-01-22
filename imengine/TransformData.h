// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_TRANSFORM_DATA
#define IMENGINE_TRANSFORM_DATA

#include "imengine/DataGrid.h"

#include <cassert>

namespace imengine {
    class InterpolationData;
    // Stores complex discrete Fourier transform values on a square grid
	class TransformData : public DataGrid {
	public:
	    // Creates a new transform data grid for the specified real-space target grid
        TransformData(InterpolationData &target);
		virtual ~TransformData();
		
		// returns the real and imaginary components of element (i,j)
        double const getReal(int i, int j) const;
        double const getImag(int i, int j) const;
        
        // writes a real value into the target InterpolationGrid
        void setTargetValue(int i, int j, double value);
        
        // calculates and returns re*re + im*im (no range checks on i,j)
        double absSquared(int i, int j) const;

        // returns the wavenumber associated an index value (no range check on i)
        double waveNumber(int i) const;
        
        // sets our values to the element-by-element product of two other transforms,
        // including an optional translation to be applied analytically via a complex
        // exponential factor exp(-ik.dr)
        void setToProduct(TransformData const& t1, TransformData const& t2, double dx=0, double dy=0);
        
        // dumps grid absolute-squared values to std::cout in row-wise order
        void dumpAbsSquared() const;

        // Calculates the real part of our inverse Fourier transform and saves the result
        // in our target InterpolationData object. Normalization is defined by:
        // data[m,n] = 1/N^2 Re[Sum[transform[j,k] Exp[+2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]]
        virtual void inverseTransform() = 0;
        
        // Sets our contents to the discrete Fourier transform of our target InterpolationData
        // object. Normalization is defined by:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void setToTransform() = 0;

        //void validate() const;

	protected:
		// accesses the real/imag parts of transform data (no range checks on i,j)
        double& real(int i, int j);
        double& imag(int i, int j);
        double const& real(int i, int j) const;
        double const& imag(int i, int j) const;

        // returns a reference to our target
        InterpolationData &getTarget();

        // returns a pointer to our transform data array
        double *getDataPtr();

        // returns a pointer to the target data array
        double *getTargetDataPtr();
        
        double _norm;

    private:
        InterpolationData &_target;
        double *_data;
        double _dk;
	}; // TransformData

    inline double& TransformData::real(int i, int j) {
        assert(i >= 0 && i < _break1);
        assert(j >= 0 && j < _gridSize);
        return _data[2*(i + _break1*j)];
    }
    inline double& TransformData::imag(int i, int j) {
        assert(i >= 0 && i < _break1);
        assert(j >= 0 && j < _gridSize);
        return _data[2*(i + _break1*j)+1];
    }
    inline double const& TransformData::real(int i, int j) const {
        assert(i >= 0 && i < _break1);
        assert(j >= 0 && j < _gridSize);
        return _data[2*(i + _break1*j)];
    }
    inline double const& TransformData::imag(int i, int j) const {
        assert(i >= 0 && i < _break1);
        assert(j >= 0 && j < _gridSize);
        return _data[2*(i + _break1*j)+1];
    }
    
    inline double TransformData::absSquared(int i, int j) const {
        assert(i >= 0 && i < _gridSize);
        assert(j >= 0 && j < _gridSize);
        double re(getReal(i,j)), im(getImag(i,j));
        return re*re + im*im;
    }

    inline double TransformData::waveNumber(int i) const {
        assert(i >= 0 && i < _gridSize);
        return _dk*(i < _break1 ? i : i-_gridSize);
    }
    
    inline double *TransformData::getDataPtr() {
        return _data;
    }
    
    inline InterpolationData &TransformData::getTarget() {
        return _target;
    }
    
} // imengine

#endif // IMENGINE_TRANSFORM_DATA

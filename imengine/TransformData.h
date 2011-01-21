// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_TRANSFORM_DATA
#define IMENGINE_TRANSFORM_DATA

#include "imengine/DataGrid.h"

namespace imengine {
    class InterpolationData;
    // Stores complex discrete Fourier transform values on a square grid
	class TransformData : public DataGrid {
	public:
	    // Creates a new transform data grid for the specified real-space target grid
        TransformData(InterpolationData &target);
		virtual ~TransformData();
		
		// accesses the real/imag parts of transform data (no range checks on i,j)
        double& real(int i, int j);
        double& imag(int i, int j);
        double const& real(int i, int j) const;
        double const& imag(int i, int j) const;
        
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
        
        // Sets our contents to the discrete Fourier transform of the specified row-wise
        // real 2D data array, normalized so that:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void setToTransform(double const *realData) = 0;

	protected:
        InterpolationData &_target;
        double _norm;
        double *_data;

    private:
        double _dk;
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

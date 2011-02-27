// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformData.h"
#include "imengine/InterpolationData.h"

#include "fftw3.h"

#include <cassert>
#include <cmath>
#include <cstdio>

namespace local = imengine;

local::TransformData::TransformData(boost::shared_ptr<InterpolationData> target) :
DataGrid(target->getGridSize(),target->getGridSpacing()), _target(target)
{
    double twopi = 8*std::atan(1.0);
    _dk = twopi/(_gridSize*_gridSpacing);
    // use FFTW allocator for best SIMD alignment
    assert(sizeof(Complex) == sizeof(fftw_complex));
    _data = (double*)fftw_malloc(sizeof(Complex)*_gridSize*_break1);
}

local::TransformData::~TransformData() {
    fftw_free(_data);
}

double const local::TransformData::getReal(int i, int j) const {
    assert(i >= 0 && i < _gridSize);
    assert(j >= 0 && j < _gridSize);
    int N(_gridSize);
    if(i < _break1) {
        return real(i,j);
    }
    else if(j == 0) {
        return real(N-i,0);
    }
    else if(2*j == N) {
        return real(N-i,j);
    }
    else {
        return real(N-i,N-j);
    }
}

double const local::TransformData::getImag(int i, int j) const {
    assert(i >= 0 && i < _gridSize);
    assert(j >= 0 && j < _gridSize);
    int N(_gridSize);
    if(i < _break1) {
        return imag(i,j);
    }
    else if(j == 0) {
        return -imag(N-i,0);
    }
    else if(2*j == N) {
        return -imag(N-i,j);
    }
    else {
        return -imag(N-i,N-j);
    }
}

void local::TransformData::tabulate(local::TransformData::Tabulator tabulator) {
    Complex value;
    for(int j = 0; j < _gridSize; ++j) {
        double ky(waveNumber(j));
        for(int i = 0; i < _break1; ++i) {
            double kx(waveNumber(i));
            tabulator(kx,ky,reinterpret_cast<Complex&>(real(i,j)));
        }
    }
}

double local::TransformData::getTargetValue(int i, int j) const {
    _target->getValue(i,j);
}

void local::TransformData::setTargetValue(int i, int j, double value) {
    _target->setValue(i,j,value);
}

double *local::TransformData::getTargetDataPtr() {
    return _target->_data;
}

void local::TransformData::setToProduct(local::TransformData const& t1,
local::TransformData const& t2, double dx, double dy) {
    // is there any translation to apply?
    bool translated = (0 != dx)||(0 != dy);
    double norm = _gridSpacing*_gridSpacing;
    for(int j = 0; j < _gridSize; ++j) {
        for(int i = 0; i < _break1; ++i) {
            double re1(t1.real(i,j)),im1(t1.imag(i,j)),re2(t2.real(i,j)),im2(t2.imag(i,j));
            double re = norm*(re1*re2 - im1*im2);
            double im = norm*(re1*im2 + im1*re2);
            if(translated) {
                double theta = -(waveNumber(i)*dx + waveNumber(j)*dy);
                // coerce the symmetry required for a real-valued inverse DFT
                if(2*i == _gridSize && j >= _break1) {
                    theta = -(-waveNumber(i)*dx + waveNumber(j)*dy);
                }
                double costh = std::cos(theta);
                double sinth = std::sin(theta);
                real(i,j) = re*costh - im*sinth;
                imag(i,j) = re*sinth + im*costh;
            }
            else {
                real(i,j) = re;
                imag(i,j) = im;
            }
        }
    }
    // Coerce the symmetry required for a real-valued inverse DFT. The reason that this might
    // be required is that sub-pixel translation via an exponential factor breaks the
    // symmetry when _gridSize is even.
    if(_gridSize % 2 == 0) {
       int nby2(_gridSize >> 1);
       imag(nby2,0) = 0;
       imag(0,nby2) = 0;
       imag(nby2,nby2) = 0;
    }
}

/**
void local::TransformData::validate() const {
    int N = _gridSize;
    for(int j = 0; j < _gridSize; j++) {
        //int j2 = (j == 0) ? 0 : N-j;
        //int sign = (N%2 == 0 && j == N/2) ? -1 : +1;
        for(int i = 0; i < _gridSize; i++) {
            if(std::fabs(getReal(i,j)-real(i,j)) > 1e-10) {
                std::cout << "re(" << i << ',' << j << ") " << getReal(i,j) << ' ' << real(i,j) << std::endl;
            }
            if(std::fabs(getImag(i,j)-imag(i,j)) > 1e-10) {
                std::cout << "im(" << i << ',' << j << ") " << getImag(i,j) << ' ' << imag(i,j) << std::endl;
            }
        }
    }
}
**/

void local::TransformData::dump() const {
    for(int j = 0; j < _gridSize; j++) {
        for(int i = 0; i < _gridSize; i++) {
            printf("[%3d,%3d] %10g + I %10g\n",i,j,getReal(i,j),getImag(i,j));
        }
    }
}

// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformData.h"
#include "imengine/InterpolationData.h"
#include "imengine/fftw.h"

#include <cassert>
#include <cmath>
#include <cstdio>

namespace local = imengine;

local::TransformData::TransformData(InterpolationDataPtr target) :
DataGrid(target->getGridSize(),target->getGridSpacing()), _target(target)
{
    double twopi = 8*std::atan(1.0);
    _dk = twopi/(_gridSize*_gridSpacing);
    // use FFTW allocator for best SIMD alignment
    assert(sizeof(Complex) == 2*sizeof(Real));
    assert(sizeof(Complex) == sizeof(FFTW(complex)));
    _data = (Real*)FFTW(malloc)(sizeof(Complex)*_gridSize*_break1);
}

local::TransformData::~TransformData() {
    FFTW(free)(_data);
}

local::Real const local::TransformData::getReal(int i, int j) const {
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

local::Real const local::TransformData::getImag(int i, int j) const {
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

local::Real local::TransformData::getTargetValue(int i, int j) const {
    return _target->getValue(i,j);
}

void local::TransformData::setTargetValue(int i, int j, Real value) {
    _target->setValue(i,j,value);
}

local::Real *local::TransformData::getTargetDataPtr() const {
    return _target->_data;
}

void local::TransformData::_translate(Real &re, Real &im,
double dx, double dy, int i, int j) {
    // calculate the argument of the translation transform
    Real theta = -(waveNumber(i)*dx + waveNumber(j)*dy);
    // coerce the symmetry required for a real-valued inverse DFT
    if(2*i == _gridSize && j >= _break1) {
        theta = -(-waveNumber(i)*dx + waveNumber(j)*dy);
    }
    Real costh = std::cos(theta);
    Real sinth = std::sin(theta);
    Real re0(re),im0(im);
    re = re0*costh - im0*sinth;
    im = re0*sinth + im0*costh;    
}

void local::TransformData::setToProduct(TransformDataPtr t1, TransformDataPtr t2,
double dx, double dy) {
    // is there any translation to apply?
    bool translated = (0 != dx)||(0 != dy);
    double norm = _gridSpacing*_gridSpacing;
    for(int j = 0; j < _gridSize; ++j) {
        for(int i = 0; i < _break1; ++i) {
            Real re1(t1->real(i,j)),im1(t1->imag(i,j));
            Real re2(t2->real(i,j)),im2(t2->imag(i,j));
            Real re = norm*(re1*re2 - im1*im2);
            Real im = norm*(re1*im2 + im1*re2);
            if(translated) _translate(re,im,dx,dy,i,j);
            real(i,j) = re;
            imag(i,j) = im;
        }
    }
    // Coerce the symmetry required for a real-valued inverse DFT. The reason that
    // this might be required is that sub-pixel translation via an exponential factor
    // breaks the symmetry when _gridSize is even.
    if(_gridSize % 2 == 0) {
       int nby2(_gridSize >> 1);
       imag(nby2,0) = 0;
       imag(0,nby2) = 0;
       imag(nby2,nby2) = 0;
    }
}

void local::TransformData::setToSum(TransformDataPtr t1, TransformDataPtr t2,
double c1, double c2, double dx, double dy) {
    bool translated = (0 != dx)||(0 != dy);
    for(int j = 0; j < _gridSize; ++j) {
        for(int i = 0; i < _break1; ++i) {
            Real re1(c1*t1->real(i,j)),im1(c1*t1->imag(i,j));
            Real re2(c2*t2->real(i,j)),im2(c2*t2->imag(i,j));
            if(translated) _translate(re2,im2,dx,dy,i,j);
            real(i,j) = re1 + re2;
            imag(i,j) = im1 + im2;
        }
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
                std::cout << "re(" << i << ',' << j << ") " << getReal(i,j)
                    << ' ' << real(i,j) << std::endl;
            }
            if(std::fabs(getImag(i,j)-imag(i,j)) > 1e-10) {
                std::cout << "im(" << i << ',' << j << ") " << getImag(i,j)
                    << ' ' << imag(i,j) << std::endl;
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

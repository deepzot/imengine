// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformData.h"

#include <cassert>
#include <cmath>
#include <iostream>

namespace local = imengine;

local::TransformData::TransformData(int gridSize, double gridSpacing, double gridX, double gridY) :
_gridSize(gridSize), _gridSpacing(gridSpacing), _gridX(gridX), _gridY(gridY)
{
    assert(gridSize > 0);
    assert(gridSpacing > 0);
    _break = gridSize/2 + 1;
    _dk = 1/(gridSize*gridSpacing);
    _norm = 1.0/gridSize;
    _data = new double[2*gridSize*gridSize];
}

local::TransformData::~TransformData() {
    delete[] _data;
}

local::TransformData *local::TransformData::createFromPrototype(local::TransformData const &prototype) {
    return new local::TransformData(prototype._gridSize,prototype._gridSpacing,
        prototype._gridX,prototype._gridY);
}

void local::TransformData::inverseTransform(double *realData) const {
    double dtheta = +8*std::atan(1.0)/_gridSize; // +2pi/N
    for(int i = 0; i < _gridSize; i++) {
        for(int j = 0; j < _gridSize; j++) {
            double value(0);
            for(int m = 0; m < _gridSize; m++) {
                for(int n = 0; n < _gridSize; n++) {
                    double theta = dtheta*(m*i + n*j);                    
                    value += real(m,n)*std::cos(theta) - imag(m,n)*std::sin(theta);
                }
            }
            realData[j + _gridSize*i] = value;
        }
    } 
}

double local::TransformData::setToTransform(double const *realData) {
    double dtheta = -8*std::atan(1.0)/_gridSize; // -2pi/N
    for(int i = 0; i < _gridSize; i++) {
        for(int j = 0; j < _gridSize; j++) {
            double re(0), im(0);
            for(int m = 0; m < _gridSize; m++) {
                for(int n = 0; n < _gridSize; n++) {
                    double value = realData[n + _gridSize*m];
                    double theta = dtheta*(m*i + n*j);
                    re += value*std::cos(theta);
                    im += value*std::sin(theta);
                }
            }
            real(i,j) = re;
            imag(i,j) = im;
        }
    }
    // return the appropriate normalization factor
    return _norm;
}

void local::TransformData::setToProduct(local::TransformData const& t1, local::TransformData const& t2, 
double norm) {
    for(int i = 0; i < _gridSize; i++) {
        for(int j = 0; j < _gridSize; j++) {
            double re1(t1.real(i,j)),im1(t1.imag(i,j)),re2(t2.real(i,j)),im2(t2.imag(i,j));
            real(i,j) = norm*(re1*re2 - im1*im2);
            imag(i,j) = norm*(re1*im2 + im1*re2);
        }
    }
}
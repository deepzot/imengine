// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/SlowTransform.h"
#include "imengine/InterpolationData.h"

#include <cmath>

namespace local = imengine;

local::SlowTransform::SlowTransform(int gridSize, double gridSpacing)
: TransformData(gridSize,gridSpacing)
{
}

local::SlowTransform::~SlowTransform() { }

local::SlowTransform *local::SlowTransform::createFromPrototype(local::DataGrid const &prototype) {
    return new local::SlowTransform(prototype.getGridSize(),prototype.getGridSpacing());
}

void local::SlowTransform::inverseTransform(InterpolationData &result) const {
    double dtheta = +8*std::atan(1.0)/_gridSize; // +2pi/N
    for(int j = 0; j < _gridSize; j++) {
        for(int i = 0; i < _gridSize; i++) {
            double re(0);
            for(int n = 0; n < _gridSize; n++) {
                for(int m = 0; m < _gridSize; m++) {
                    double theta = dtheta*(m*i + n*j);                    
                    re += _norm*(real(m,n)*std::cos(theta) - imag(m,n)*std::sin(theta));
                }
            }
            result.setValue(i,j,re);
        }
    }
}

void local::SlowTransform::setToTransform(double const *realData) {
    double dtheta = -8*std::atan(1.0)/_gridSize; // -2pi/N
    for(int j = 0; j < _gridSize; j++) {
        for(int i = 0; i < _gridSize; i++) {
            double re(0), im(0);
            for(int n = 0; n < _gridSize; n++) {
                for(int m = 0; m < _gridSize; m++) {
                    double value = realData[m + _gridSize*n];
                    double theta = dtheta*(m*i + n*j);
                    re += value*std::cos(theta);
                    im += value*std::sin(theta);
                }
            }
            real(i,j) = re;
            imag(i,j) = im;
        }
    }
}


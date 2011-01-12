// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/GenericPixelFunction.h"
#include "imengine/TransformData.h"

#include <cassert>
#include <iostream>
#include <cmath>

namespace local = imengine;

local::GenericPixelFunction::GenericPixelFunction() :
AbsPixelFunction(), _data(0)
{
}

local::GenericPixelFunction::~GenericPixelFunction() {
    if(0 != _data) delete[] _data;
}

void local::GenericPixelFunction::initTransform(TransformData* transformData) {
    assert(0 != transformData);
    _transformData = transformData;
    int ngrid = _transformData->getGridSize();
    _data = new double[ngrid*ngrid];
}

void local::GenericPixelFunction::doTransform(double dx, double dy) const {
    // tabulate function values on a (x,y) grid
    double *ptr = _data;
    int ngrid = _transformData->getGridSize();
    double spacing = _transformData->getGridSpacing();
    double dtheta = -8*std::atan(1.0)/ngrid;
    for(int i = 0; i < ngrid; i++) {
        double x = _transformData->getX(i);
        for(int j = 0; j < ngrid; j++) {
            double y = _transformData->getY(j);
            double value = (*this)(x,y);
            *ptr++ = value;
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "=== TRANSFORM ===" << std::endl;
    // calculate the discrete (un-normalized) Fourier transform of the tabulated data
    for(int i = 0; i < ngrid; i++) {
        for(int j = 0; j < ngrid; j++) {
            double real(0), imag(0);
            for(int m = 0; m < ngrid; m++) {
                for(int n = 0; n < ngrid; n++) {
                    double value = _data[n + ngrid*m];
                    double theta = dtheta*(m*i + n*j);
                    real += value*std::cos(theta);
                    imag += value*std::sin(theta);
                }
            }
            _transformData->real(i,j) = real;
            _transformData->imag(i,j) = imag;
        }
    }
    return;
}
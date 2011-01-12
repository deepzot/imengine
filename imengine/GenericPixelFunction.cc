// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/GenericPixelFunction.h"
#include "imengine/TransformData.h"

#include <cassert>
#include <iostream>

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

double local::GenericPixelFunction::doTransform(double dx, double dy) const {
    // tabulate function values on a (x,y) grid
    double *ptr = _data;
    int ngrid = _transformData->getGridSize();
    double spacing = _transformData->getGridSpacing();
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
    std::cout << "------------" << std::endl;
    // calculate the discrete Fourier transform of the tabulated data
    return _transformData->setToTransform(_data);
}
// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/GenericPixelFunction.h"
#include "imengine/TransformData.h"

#include <cassert>

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
    double total(0);
    for(int j = 0; j < ngrid; j++) {
        double y = _transformData->getY(j) - dy;
        for(int i = 0; i < ngrid; i++) {
            double x = _transformData->getX(i) - dx;
            double value = (*this)(x,y);
            *ptr++ = value;
            total += value;
        }
    }
    double spacing = _transformData->getGridSpacing();
    // calculate the discrete Fourier transform of the tabulated data
    _transformData->setToTransform(_data);
}
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
    _break = ngrid/2 + 1;
}

void local::GenericPixelFunction::doTransform(double dx, double dy) const {
    // tabulate function values on a (x,y) grid
    double x,y;
    double *ptr = _data;
    int ngrid = _transformData->getGridSize();
    double spacing = _transformData->getGridSpacing();
    for(int i = 0; i < ngrid; i++) {
        if(i < _break) {
            x = dx + i*spacing;
        }
        else {
            x = dx + (ngrid - i)*spacing;
        }
        for(int j = 0; j < ngrid; j++) {
            if(j < _break) {
                y = dy + j*spacing;
            }
            else {
                y = dy + (ngrid - j)*spacing;
            }
            *ptr++ = (*this)(x,y);
        }
    }
    // calculate the discrete Fourier transform of the tabulated data
    // ...
    return;
}
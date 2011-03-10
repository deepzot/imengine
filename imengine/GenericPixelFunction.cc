// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/GenericPixelFunction.h"
#include "imengine/TransformData.h"

namespace local = imengine;

local::GenericPixelFunction::GenericPixelFunction() :
AbsPixelFunction()
{
}

local::GenericPixelFunction::~GenericPixelFunction() {
}

void local::GenericPixelFunction::doTransform(TransformDataPtr transformData) {
    // tabulate function values on a (x,y) grid
    int ngrid = transformData->getGridSize();
    for(int j = 0; j < ngrid; j++) {
        double y = transformData->getY(j);
        for(int i = 0; i < ngrid; i++) {
            double x = transformData->getX(i);
            double value = (*this)(x,y);
            transformData->setTargetValue(i,j,value);
        }
    }
    // calculate the discrete Fourier transform of the tabulated data
    transformData->setToTransform();
}
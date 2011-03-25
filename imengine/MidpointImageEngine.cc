// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/MidpointImageEngine.h"
#include "imengine/InterpolationData.h"

namespace local = imengine;

template <class T>
local::MidpointImageEngine<T>::MidpointImageEngine(
AbsPixelFunctionPtr source, AbsPixelFunctionPtr psf)
: ImageEngine<T>(source,psf)
{
}

template <class T>
local::MidpointImageEngine<T>::~MidpointImageEngine() { }

template <class T>
local::InterpolationData* local::MidpointImageEngine<T>::createGrid() {
    // Put a grid point in the center of each pixel...
    int size = this->getPixelsPerSide();
    double scale = this->getPixelScale();
    this->_norm = this->getPixelScaleSquared()/(size*size);
    // for an odd number of pixels, the grid is already centered on the pixel array but
    // an even number of pixels requires a half-pixel offset
    double offset = (size % 2) ? 0 : -scale/2;
    return new local::InterpolationData(size,0,scale,offset,offset);
}

template <class T>
double local::MidpointImageEngine<T>::estimatePixelValue(int x, int y) {
    return this->_norm*this->_imageGrid->getValueForPixel(x,y);
}

// explicit template instantiations

#include "imengine/SlowTransform.h"
template class local::MidpointImageEngine<local::SlowTransform>;

#include "imengine/FastTransform.h"
template class local::MidpointImageEngine<local::FastTransform>;
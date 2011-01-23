// Created 16-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/BilinearImageEngine.h"
#include "imengine/InterpolationData.h"

namespace local = imengine;

template <class T>
local::BilinearImageEngine<T>::BilinearImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf) :
ImageEngine<T>(source,psf)
{
}

template <class T>
local::BilinearImageEngine<T>::~BilinearImageEngine() { }

template <class T>
local::InterpolationData* local::BilinearImageEngine<T>::createGrid() {
    // Put a grid point at the corners of each pixel
    int size = this->getPixelsPerSide() + 1;
    double scale = this->getPixelScale();
    _norm = this->_scaleSquared/(4*size*size);
    // for an odd number of pixels, the grid is already centered on the pixel array but
    // an even number of pixels requires a half-pixel offset
    double offset = (size % 2) ? 0 : -scale/2;
    return new local::InterpolationData(size,0,scale,offset,offset);
}

template <class T>
double local::BilinearImageEngine<T>::estimatePixelValue(int x, int y) {
    return this->_norm*(
        _imageGrid->getValueForPixel(x,y) + _imageGrid->getValueForPixel(x+1,y) +
        _imageGrid->getValueForPixel(x,y+1) + _imageGrid->getValueForPixel(x+1,y+1));
}

// explicit template instantiations

#include "imengine/SlowTransform.h"
template class local::BilinearImageEngine<local::SlowTransform>;

#include "imengine/FastTransform.h"
template class local::BilinearImageEngine<local::FastTransform>;

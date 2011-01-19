// Created 16-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/BicubicImageEngine.h"
#include "imengine/InterpolationData.h"

namespace local = imengine;

template <class T>
local::BicubicImageEngine<T>::BicubicImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
ImageEngine<T>(source,psf,pixelsPerSide,pixelScale)
{
    _norm1 = this->_scaleSquared/576.;
    _norm13 = -13*this->_scaleSquared/576.;
    _norm169 = 169*this->_scaleSquared/576.;
}

template <class T>
local::BicubicImageEngine<T>::~BicubicImageEngine() { }

template <class T>
local::InterpolationData* local::BicubicImageEngine<T>::createGrid() {
    // Put a grid point at the corners of each pixel
    int size = this->getPixelsPerSide() + 3;
    double scale = this->getPixelScale();
    // for an odd number of pixels, the grid is already centered on the pixel array but
    // an even number of pixels requires a half-pixel offset
    double offset = (size % 2) ? 0 : -scale/2;
    // add padding around the grid so we can estimate partial derivatives at
    // the outer pixel corners
    return new local::InterpolationData(size,1,scale,offset,offset);
}

template <class T>
double local::BicubicImageEngine<T>::estimatePixelValue(int x, int y) {
    return
        _norm169*(
            _imageGrid->getValueForPixel(x,y) + _imageGrid->getValueForPixel(x+1,y) +
            _imageGrid->getValueForPixel(x,y+1) + _imageGrid->getValueForPixel(x+1,y+1)
        ) +
        _norm13*(
            _imageGrid->getValueForPixel(x-1,y) + _imageGrid->getValueForPixel(x-1,y+1) +
            _imageGrid->getValueForPixel(x,y+2) + _imageGrid->getValueForPixel(x+1,y+2) +
            _imageGrid->getValueForPixel(x+2,y+1) + _imageGrid->getValueForPixel(x+2,y) +
            _imageGrid->getValueForPixel(x+1,y-1) + _imageGrid->getValueForPixel(x,y-1)
        ) +
        _norm1*(
            _imageGrid->getValueForPixel(x-1,y-1) + _imageGrid->getValueForPixel(x-1,y+2) +
            _imageGrid->getValueForPixel(x+2,y+2) + _imageGrid->getValueForPixel(x+2,y-1)
        );
}

// explicit template instantiations

#include "imengine/TransformData.h"
template class local::BicubicImageEngine<local::TransformData>;

#include "imengine/FastTransformData.h"
template class local::BicubicImageEngine<local::FastTransformData>;
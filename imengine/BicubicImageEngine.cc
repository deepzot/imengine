// Created 16-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/BicubicImageEngine.h"
#include "imengine/InterpolationData.h"

#include <iostream>

namespace local = imengine;

template <class T>
local::BicubicImageEngine<T>::BicubicImageEngine(
AbsPixelFunctionPtr source, AbsPixelFunctionPtr psf, double threshold)
: ImageEngine<T>(source,psf), _threshold(threshold), _rescale(144./169.)
{
}

template <class T>
local::BicubicImageEngine<T>::~BicubicImageEngine() { }

template <class T>
local::InterpolationData* local::BicubicImageEngine<T>::createGrid() {
    int N(this->getPixelsPerSide());
    // Calculate the actual threshold to apply on the partial bicubic result.
    _actualThreshold = _threshold/(_rescale*N*N);
    // Put a grid point at the corners of each pixel
    int size(N + 3);
    double scale(this->getPixelScale());
    double tmp(24*size*scale);
    _norm1 = 1/(tmp*tmp);
    _norm13 = -13*_norm1;
    _norm169 = 169*_norm1;
    // for an odd number of pixels, the grid is already centered on the pixel array but
    // an even number of pixels requires a half-pixel offset
    double offset = (size % 2) ? 0 : -scale/2;
    // add padding around the grid so we can estimate partial derivatives at
    // the outer pixel corners
    return new InterpolationData(size,1,scale,offset,offset);
}

template <class T>
double local::BicubicImageEngine<T>::estimatePixelValue(int x, int y) {
    double linearApprox(_norm169*(
        _imageGrid->getValueForPixel(x,y) + _imageGrid->getValueForPixel(x+1,y) +
        _imageGrid->getValueForPixel(x,y+1) + _imageGrid->getValueForPixel(x+1,y+1)));
    if(linearApprox >= _actualThreshold) {
        double cubicAdjust(
            _norm13*(
                _imageGrid->getValueForPixel(x-1,y) + _imageGrid->getValueForPixel(x-1,y+1) +
                _imageGrid->getValueForPixel(x,y+2) + _imageGrid->getValueForPixel(x+1,y+2) +
                _imageGrid->getValueForPixel(x+2,y+1) + _imageGrid->getValueForPixel(x+2,y) +
                _imageGrid->getValueForPixel(x+1,y-1) + _imageGrid->getValueForPixel(x,y-1)
            ) +
            _norm1*(
                _imageGrid->getValueForPixel(x-1,y-1) + _imageGrid->getValueForPixel(x-1,y+2) +
                _imageGrid->getValueForPixel(x+2,y+2) + _imageGrid->getValueForPixel(x+2,y-1)
            ));
        return linearApprox + cubicAdjust;
    }
    else {
        // Rescale the partial bicubic result to a bilinear interpolation.
        return linearApprox*_rescale;
    }
}

// explicit template instantiations

#include "imengine/SlowTransform.h"
template class local::BicubicImageEngine<local::SlowTransform>;

#include "imengine/FastTransform.h"
template class local::BicubicImageEngine<local::FastTransform>;

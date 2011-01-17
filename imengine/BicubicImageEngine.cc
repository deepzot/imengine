// Created 16-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/BicubicImageEngine.h"
#include "imengine/InterpolationData.h"

namespace local = imengine;

local::BicubicImageEngine::BicubicImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
ImageEngine(source,psf,pixelsPerSide,pixelScale)
{
    _norm1 = _scaleSquared/576.;
    _norm13 = -13*_scaleSquared/576.;
    _norm169 = 169*_scaleSquared/576.;
}

local::BicubicImageEngine::~BicubicImageEngine() { }

local::InterpolationData* local::BicubicImageEngine::createGrid() {
    // Put a grid point at the corners of each pixel
    int size = getPixelsPerSide() + 3;
    double scale = getPixelScale();
    // for an odd number of pixels, the grid is already centered on the pixel array but
    // an even number of pixels requires a half-pixel offset
    double offset = (size % 2) ? 0 : -scale/2;
    // add padding around the grid so we can estimate partial derivatives at
    // the outer pixel corners
    return new local::InterpolationData(size,1,scale,offset,offset);
}

double local::BicubicImageEngine::estimatePixelValue(int x, int y) {
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
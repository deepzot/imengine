// Created 16-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/BilinearImageEngine.h"
#include "imengine/InterpolationData.h"

namespace local = imengine;

local::BilinearImageEngine::BilinearImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
ImageEngine(source,psf,pixelsPerSide,pixelScale)
{
    _norm = _scaleSquared/4;
}

local::BilinearImageEngine::~BilinearImageEngine() { }

local::InterpolationData* local::BilinearImageEngine::createGrid() {
    // Put a grid point at the corners of each pixel
    int size = getPixelsPerSide() + 1;
    double scale = getPixelScale();
    // for an odd number of pixels, the grid is already centered on the pixel array but
    // an even number of pixels requires a half-pixel offset
    double offset = (size % 2) ? 0 : -scale/2;
    return new local::InterpolationData(size,0,scale,offset,offset);
}

double local::BilinearImageEngine::estimatePixelValue(int x, int y) {
    return _norm*(
        _imageGrid->getValueForPixel(x,y) + _imageGrid->getValueForPixel(x+1,y) +
        _imageGrid->getValueForPixel(x,y+1) + _imageGrid->getValueForPixel(x+1,y+1));
}
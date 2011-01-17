// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/MidpointImageEngine.h"
#include "imengine/InterpolationData.h"

namespace local = imengine;

local::MidpointImageEngine::MidpointImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
ImageEngine(source,psf,pixelsPerSide,pixelScale)
{
}

local::MidpointImageEngine::~MidpointImageEngine() { }

local::InterpolationData* local::MidpointImageEngine::createGrid() {
    // Put a grid point in the center of each pixel...
    int size = getPixelsPerSide();
    double scale = getPixelScale();
    // for an odd number of pixels, the grid is already centered on the pixel array but
    // an even number of pixels requires a half-pixel offset
    double offset = (size % 2) ? 0 : -scale/2;
    return new local::InterpolationData(size,0,scale,offset,offset);
}

double local::MidpointImageEngine::estimatePixelValue(int x, int y) {
    return _scaleSquared*_imageGrid->getValueForPixel(x,y);
}
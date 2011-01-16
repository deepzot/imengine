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
    if(size % 2 == 1) {
        // for an odd number of pixels, the grid is already centered on the pixel array
        return new local::InterpolationData(size,0,scale,0,0);
    }
    else {
        // an even number of pixels requires a half-pixel offset
        return new local::InterpolationData(size,0,scale,-scale/2,-scale/2);
    }
}

double local::MidpointImageEngine::estimatePixelValue(int x, int y) {
    return _scaleSquared*_imageGrid->getValueForPixel(x,y);
}
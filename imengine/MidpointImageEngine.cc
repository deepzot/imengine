// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/MidpointImageEngine.h"
#include "imengine/TransformData.h"

namespace local = imengine;

local::MidpointImageEngine::MidpointImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
ImageEngine(source,psf,pixelsPerSide,pixelScale)
{    
}

local::MidpointImageEngine::~MidpointImageEngine() { }

local::TransformData* local::MidpointImageEngine::createImageTransform() {
    // Put a grid point in the center of each pixel...
    int size = getPixelsPerSide();
    double dx = getPixelScale();
    if(size % 2 == 1) {
        // for an odd number of pixels, the grid is already centered on the pixel array,
        return new local::TransformData(size,dx,0,0);
    }
    else {
        // an even number of pixels requires padding the top and one side of the grid
        // and introduces a half-pixel offset.
        return new local::TransformData(size+1,dx,-dx/2,-dx/2);
    }
}

double local::MidpointImageEngine::estimatePixelValue(int i, int j) {
    return 0;
}
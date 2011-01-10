// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/MidpointImageEngine.h"

namespace local = imengine;

local::MidpointImageEngine::MidpointImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
ImageEngine(source,psf,pixelsPerSide,pixelScale)
{    
}

local::MidpointImageEngine::~MidpointImageEngine() { }

void local::ImageEngine::setGridParams() {
    // Put a grid point in the center of each pixel...
    gridSize = getPixelsPerSide();
    gridSpacing = getPixelScale();
    // For an odd number of pixels, the grid is already centered on the pixel array,
    // but an even number of pixels requires padding the top and one side of the grid
    // and introduces a half-pixel offset.
    if(gridSize % 2 == 0) {
        gridSize++;
        gridX = gridY = -gridSpacing/2;
    }
    else {
        gridX = gridY = 0;        
    }
}
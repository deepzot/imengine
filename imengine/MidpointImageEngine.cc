// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/MidpointImageEngine.h"

namespace local = imengine;

local::MidpointImageEngine::MidpointImageEngine(const local::AbsPixelFunction& source, 
const local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
ImageEngine(source,psf,pixelsPerSide,pixelScale)
{    
}

local::MidpointImageEngine::~MidpointImageEngine() { }

void local::ImageEngine::setGridParams() {
    // put a grid point in the center of each pixel
    gridSize = getPixelsPerSide();
    gridSpacing = getPixelScale();
}
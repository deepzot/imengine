// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ImageEngine.h"
#include "imengine/AbsPixelFunction.h"

namespace local = imengine;

local::ImageEngine::ImageEngine(const local::AbsPixelFunction& source, 
const local::AbsPixelFunction& psf, int pixelsPerSide) {
    
}

local::ImageEngine::~ImageEngine() { }

local::ImageData *local::ImageEngine::generate(double pixelScale, double dx, double dy) {
    return 0;
}
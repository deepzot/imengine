// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ImageEngine.h"
#include "imengine/AbsPixelFunction.h"

#include <cassert>

namespace local = imengine;

local::ImageEngine::ImageEngine(const local::AbsPixelFunction& source, 
const local::AbsPixelFunction& psf, int pixelsPerSide) :
_source(source), _psf(psf), _pixelsPerSide(pixelsPerSide),
_sourceTransform(0), _psfTransform(0), _imageTransform(0)
{
    assert(pixelsPerSide > 0);
}

local::ImageEngine::~ImageEngine() { }

local::ImageData *local::ImageEngine::generate(double pixelScale, double dx, double dy) {
    return 0;
}
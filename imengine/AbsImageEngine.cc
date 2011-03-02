// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/AbsImageEngine.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/InterpolationData.h"

#include <cassert>

namespace local = imengine;

local::AbsImageEngine::AbsImageEngine(boost::shared_ptr<local::AbsPixelFunction> source,
    boost::shared_ptr<local::AbsPixelFunction> psf)
: _source(source), _psf(psf), _initialized(false)
{
}

local::AbsImageEngine::~AbsImageEngine() { }

void local::AbsImageEngine::initialize(int pixelsPerSide, double pixelScale) {
    assert(pixelsPerSide > 0);
    assert(pixelScale > 0);
    _pixelsPerSide = pixelsPerSide;
    _pixelScale = pixelScale;
    _scaleSquared = pixelScale*pixelScale;
    _initialized = true;    
}
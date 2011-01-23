// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/AbsImageEngine.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/InterpolationData.h"

#include <cassert>

namespace local = imengine;

local::AbsImageEngine::AbsImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf) :
_source(source), _psf(psf), _initialized(false), _imageGrid(0), _workspace(0)
{
}

local::AbsImageEngine::~AbsImageEngine() {
    _reset();
}

void local::AbsImageEngine::_reset() {
    if(_initialized) {
        delete _imageGrid;
        delete _workspace;
    }    
}
void local::AbsImageEngine::initialize(int pixelsPerSide, double pixelScale) {
    assert(pixelsPerSide > 0);
    assert(pixelScale > 0);
    _reset();
    _pixelsPerSide = pixelsPerSide;
    _pixelScale = pixelScale;
    _scaleSquared = pixelScale*pixelScale;
    _initialized = true;    
}
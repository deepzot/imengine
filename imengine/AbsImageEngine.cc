// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/AbsImageEngine.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/InterpolationData.h"

#include <cassert>

namespace local = imengine;

local::AbsImageEngine::AbsImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
_source(source), _psf(psf), _pixelsPerSide(pixelsPerSide), _pixelScale(pixelScale),
_imageGrid(0), _workspace(0)
{
    assert(pixelsPerSide > 0);
    assert(pixelScale > 0);
    _scaleSquared = pixelScale*pixelScale;
}

local::AbsImageEngine::~AbsImageEngine() {
    if(0 != _imageGrid) {
        delete _imageGrid;
        delete _workspace;
    }
}

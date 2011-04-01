// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/AbsImageEngine.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/InterpolationData.h"
#include "imengine/InvalidValue.h"

namespace local = imengine;

local::AbsImageEngine::AbsImageEngine()
: _initialized(false)
{
}

local::AbsImageEngine::~AbsImageEngine() { }

void local::AbsImageEngine::initialize(int pixelsPerSide, double pixelScale) {
    assertGreaterThan<int>("AbsImageEngine pixelsPerSide",pixelsPerSide,0);
    assertGreaterThan<double>("AbsImageEngine pixelScale",pixelScale,0);
    _pixelsPerSide = pixelsPerSide;
    _pixelScale = pixelScale;
    _initialized = true;    
}

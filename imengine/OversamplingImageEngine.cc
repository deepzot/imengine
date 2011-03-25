// Created 25-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/OversamplingImageEngine.h"

#include <cassert>

namespace local = imengine;

local::OversamplingImageEngine::OversamplingImageEngine(AbsImageEnginePtr engine, int subpixels)
: _engine(engine), _subpixels(subpixels)
{
    assert(0 != _engine.get());
    assert(_subpixels >= 1);
}

local::OversamplingImageEngine::~OversamplingImageEngine() { }

void local::OversamplingImageEngine::initialize(int pixelsPerSide, double pixelScale) {
}

double local::OversamplingImageEngine::generate(AbsImageWriter &writer, double dx, double dy) {
    return 0;
}
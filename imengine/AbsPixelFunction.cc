// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/AbsPixelFunction.h"

#include <cassert>

namespace local = imengine;

local::AbsPixelFunction::AbsPixelFunction() { }

local::AbsPixelFunction::~AbsPixelFunction() { }

void local::AbsPixelFunction::initTransform(boost::shared_ptr<TransformData> transformData) {
    _transformData = transformData;
    assert(0 != _transformData.get());
}

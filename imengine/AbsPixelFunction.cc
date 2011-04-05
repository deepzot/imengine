// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/AbsPixelFunction.h"
#include "imengine/RuntimeError.h"

#include <cassert>

namespace local = imengine;

local::AbsPixelFunction::AbsPixelFunction() { }

local::AbsPixelFunction::~AbsPixelFunction() { }

void local::AbsPixelFunction::initTransform(TransformDataPtr transformData) {
    if(0 == transformData.get()) {
        throw RuntimeError("initTransform called without transform data.");
    }
    _observer.setChanged(true);
}

void local::AbsPixelFunction::computeTransform(TransformDataPtr transformData) {
    doTransform(transformData);
    _observer.setChanged(false);
}

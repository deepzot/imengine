// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/AbsPixelFunction.h"
#include "imengine/RuntimeError.h"
#include "imengine/Observer.h"

namespace local = imengine;

local::AbsPixelFunction::AbsPixelFunction()
: _observer(new Observer())
{ }

local::AbsPixelFunction::~AbsPixelFunction() { }

void local::AbsPixelFunction::initTransform(TransformDataPtr transformData) {
    if(0 == transformData.get()) {
        throw RuntimeError("initTransform called without transform data.");
    }
    _observer->setChanged(true);
}

void local::AbsPixelFunction::computeTransform(TransformDataPtr transformData) {
    doTransform(transformData);
    _observer->setChanged(false);
}

bool local::AbsPixelFunction::hasChanged() const {
    return _observer->hasChanged();
}

local::ObserverPtr local::AbsPixelFunction::getObserver() const {
    return _observer;
}

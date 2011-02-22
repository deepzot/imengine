// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformedProfileFunction.h"

#include <cassert>

namespace local = imengine;

local::TransformedProfileFunction::TransformedProfileFunction() { }

local::TransformedProfileFunction::~TransformedProfileFunction() { }

double local::TransformedProfileFunction::operator()(double x, double y) const {
    return 0;
}

void local::TransformedProfileFunction::initTransform(TransformData* transformData) {
    assert(0 != transformData);
    _transformData = transformData;
}

void local::TransformedProfileFunction::doTransform() {
}

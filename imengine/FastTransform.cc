// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/FastTransform.h"
#include "imengine/InterpolationData.h"

namespace local = imengine;

local::FastTransform::FastTransform(InterpolationData &target)
: TransformData(target)
{
}

local::FastTransform::~FastTransform() { }

void local::FastTransform::setToTransform(double const *realData) {
}

void local::FastTransform::inverseTransform() {
}
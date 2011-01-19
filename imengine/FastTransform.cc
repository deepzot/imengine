// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/FastTransform.h"
#include "imengine/InterpolationData.h"

namespace local = imengine;

local::FastTransform::FastTransform(int gridSize, double gridSpacing)
: TransformData(gridSize,gridSpacing)
{
}

local::FastTransform::~FastTransform() { }

local::FastTransform *local::FastTransform::createForTarget(local::InterpolationData& target) {
    return new local::FastTransform(target.getGridSize(),target.getGridSpacing());
}

void local::FastTransform::setToTransform(double const *realData) {
}

void local::FastTransform::inverseTransform(InterpolationData &result) const {
}
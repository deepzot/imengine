// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/FastTransformData.h"

namespace local = imengine;

local::FastTransformData::FastTransformData(int gridSize, double gridSpacing)
: TransformData(gridSize,gridSpacing)
{
}

local::FastTransformData::~FastTransformData() { }

local::FastTransformData *local::FastTransformData::createFromPrototype(local::DataGrid const &prototype) {
    return new local::FastTransformData(prototype.getGridSize(),prototype.getGridSpacing());
}

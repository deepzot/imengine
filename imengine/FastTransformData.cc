// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/FastTransformData.h"

namespace local = imengine;

local::FastTransformData::FastTransformData(int gridSize, double gridSpacing)
: TransformData(gridSize,gridSpacing)
{
}

local::FastTransformData::~FastTransformData() { }

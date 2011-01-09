// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformData.h"

#include <cassert>

namespace local = imengine;

local::TransformData::TransformData(int gridSize, double gridSpacing) :
_gridSize(gridSize), _gridSpacing(gridSpacing), _data(0)
{
    assert(gridSize > 0);
    assert(gridSpacing > 0);
}

local::TransformData::~TransformData() { }

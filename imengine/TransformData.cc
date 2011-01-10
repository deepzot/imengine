// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformData.h"

#include <cassert>

namespace local = imengine;

local::TransformData::TransformData(int gridSize, double gridSpacing) :
_gridSize(gridSize), _gridSpacing(gridSpacing)
{
    assert(gridSize > 0);
    assert(gridSpacing > 0);
    _break = gridSize/2 + 1;
    _dk = 1/(gridSize*gridSpacing);
    _data = new double[2*gridSize*gridSize];
}

local::TransformData::~TransformData() {
    delete[] _data;
}

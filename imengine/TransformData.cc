// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformData.h"

#include <cassert>

namespace local = imengine;

local::TransformData::TransformData(int gridSize, double gridSpacing, double gridX, double gridY) :
_gridSize(gridSize), _gridSpacing(gridSpacing), _gridX(gridX), _gridY(gridY)
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

local::TransformData *local::TransformData::createFromPrototype(local::TransformData const &prototype) {
    return new local::TransformData(prototype._gridSize,prototype._gridSpacing,
        prototype._gridX,prototype._gridY);
}
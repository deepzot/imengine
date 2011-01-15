// Created 14-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/InterpolationData.h"

#include <cassert>

namespace local = imengine;

local::InterpolationData::InterpolationData(int gridSize, int pad, double gridSpacing, double gridX, double gridY)
: DataGrid(gridSize,gridSpacing,gridX,gridY), _pad(pad)
{
    assert(pad >= 0 && pad < gridSize);
    _data = new double[gridSize*gridSize];
}

local::InterpolationData::~InterpolationData() { }

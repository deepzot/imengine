// Created 14-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/InterpolationData.h"

namespace local = imengine;

local::InterpolationData::InterpolationData(int gridSize, double gridSpacing, double gridX, double gridY)
: DataGrid(gridSize,gridSpacing,gridX,gridY)
{
}

local::InterpolationData::~InterpolationData() { }

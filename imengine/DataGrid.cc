// Created 13-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/DataGrid.h"

#include <cassert>

namespace local = imengine;

local::DataGrid::DataGrid(int gridSize, double gridSpacing) :
_gridSize(gridSize), _gridSpacing(gridSpacing)
{
    assert(gridSize > 0);
    assert(gridSpacing > 0);
    _break1 = gridSize/2 + 1;
    _break2 = _gridSize - _break1;
}

local::DataGrid::~DataGrid() { }

// Created 13-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/DataGrid.h"

#include <cassert>

namespace local = imengine;

local::DataGrid::DataGrid(int gridSize, double gridSpacing, double gridX, double gridY) :
_gridSize(gridSize), _gridSpacing(gridSpacing), _gridX(gridX), _gridY(gridY)
{
    assert(gridSize > 0);
    assert(gridSpacing > 0);
    _break = gridSize/2 + 1;
}

local::DataGrid::~DataGrid() { }

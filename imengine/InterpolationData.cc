// Created 14-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/InterpolationData.h"

#include <cassert>
#include <iostream>

namespace local = imengine;

local::InterpolationData::InterpolationData(int gridSize, int pad, double gridSpacing,
double gridX, double gridY)
: DataGrid(gridSize,gridSpacing), _pad(pad), _gridX(gridX), _gridY(gridY)
{
    assert(pad >= 0 && pad < gridSize);
    _data = new double[gridSize*gridSize];
}

local::InterpolationData::~InterpolationData() { }

void local::InterpolationData::dump() const {
    for(int j = 0; j < _gridSize; j++) {
        for(int i = 0; i < _gridSize; i++) {
            std::cout << _data[i + _gridSize*j] << ' ';
        }
        std::cout << std::endl;
    }
}

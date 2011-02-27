// Created 14-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/InterpolationData.h"
#include "imengine/fftw.h"

#include <cassert>
#include <iostream>

namespace local = imengine;

local::InterpolationData::InterpolationData(int gridSize, int pad, double gridSpacing,
double gridX, double gridY)
: DataGrid(gridSize,gridSpacing), _pad(pad), _gridX(gridX), _gridY(gridY)
{
    assert(pad >= 0 && pad < gridSize);
    // use FFTW allocator for best SIMD alignment
    _data = (Real*)FFTW(malloc)(sizeof(Real)*gridSize*gridSize);
}

local::InterpolationData::~InterpolationData() {
    FFTW(free)(_data);
}

void local::InterpolationData::setValue(int i, int j, Real value) {
    assert(i >= 0 && i < _gridSize);
    assert(j >= 0 && j < _gridSize);
    _data[i + _gridSize*j] = value;
}

local::InterpolationData *local::InterpolationData::createWorkspace() const {
    return new local::InterpolationData(_gridSize, _pad, _gridSpacing, _gridX, _gridY);
}

void local::InterpolationData::dump() const {
    for(int j = 0; j < _gridSize; j++) {
        for(int i = 0; i < _gridSize; i++) {
            std::cout << _data[i + _gridSize*j] << ' ';
        }
        std::cout << std::endl;
    }
}

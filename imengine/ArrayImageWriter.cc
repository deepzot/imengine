// Created 23-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ArrayImageWriter.h"

#include <cassert>

namespace local = imengine;

local::ArrayImageWriter::ArrayImageWriter()
: AbsImageWriter(), _data(0), _size(0)
{
}

local::ArrayImageWriter::~ArrayImageWriter() {
    if(0 != _data) delete [] _data;
}

void local::ArrayImageWriter::open(int size, double scale) {
    assert(size > 0);
    _size = size;
    // free the array from a previous image
    if(0 != _data) delete [] _data;
    _data = new double[size*size];
}

void local::ArrayImageWriter::write(int x, int y, double value) {
    _data[x + y*_size] = value;
}

void local::ArrayImageWriter::close() { }

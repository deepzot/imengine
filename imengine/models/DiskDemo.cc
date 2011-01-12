// Created 11-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/DiskDemo.h"

#include <cassert>
#include <cmath>

namespace local = imengine::models;

local::DiskDemo::DiskDemo(double size) :
_size(size), _sizesq(size*size)
{
    assert(size > 0);
    _invnorm = 1/(4*std::atan(1.0)*_sizesq);
}

local::DiskDemo::~DiskDemo() { }

double local::DiskDemo::operator()(double x, double y) const {
    double rsq = x*x + y*y;
    return (rsq < _sizesq) ? _invnorm : 0;
}
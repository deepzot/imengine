// Created 25-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/DiskProfile.h"

#include <cassert>
#include <cmath>

namespace local = imengine::models;

local::DiskProfile::DiskProfile(double radius) :
_radius(radius)
{
    assert(_radius > 0);
    double twopi(8*std::atan(1.0));
    _norm = 1/(twopi*_radius*_radius);
}

local::DiskProfile::~DiskProfile() { }

double local::DiskProfile::operator()(double r) const {
    return r < _radius ? _norm : 0;
}

double local::DiskProfile::radialIntegral(double kappa) const {
    double kr(kappa*_radius);
    return 0;
}
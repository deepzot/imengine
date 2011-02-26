// Created 25-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/DiskProfile.h"

#include "gsl/gsl_sf_bessel.h"

#include <cassert>
#include <cmath>

namespace local = imengine::models;

local::DiskProfile::DiskProfile(double radius) :
_radius(radius)
{
    assert(_radius > 0);
    double pi(4*std::atan(1.0));
    _norm = 1/(pi*_radius*_radius);
}

local::DiskProfile::~DiskProfile() { }

double local::DiskProfile::operator()(double r) const {
    return r < _radius ? _norm : 0;
}

double local::DiskProfile::radialIntegral(double kappa) const {
    double kr(kappa*_radius);
    return kr == 0 ? 1 : 2*gsl_sf_bessel_J1(kr)/kr;
}
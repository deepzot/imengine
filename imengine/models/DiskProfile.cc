// Created 25-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/DiskProfile.h"
#include "imengine/InvalidValue.h"

#include "gsl/gsl_sf_bessel.h"

#include <cmath>

namespace local = imengine::models;

local::DiskProfile::DiskProfile(double radius)
: _pi(4*std::atan(1.0))
{
    setParameters(radius);
}

local::DiskProfile::~DiskProfile() { }

void local::DiskProfile::setParameters(double radius) {
    if(isInitialized() && radius == _radius) return;
    assertGreaterThan<double>("DiskProfile radius",radius,0);
    _radius = radius;
    _norm = 1/(_pi*_radius*_radius);
    setChanged();
}

double local::DiskProfile::operator()(double r) const {
    return r < _radius ? _norm : 0;
}

double local::DiskProfile::radialIntegral(double kappa) const {
    double kr(kappa*_radius);
    return kr == 0 ? 1 : 2*gsl_sf_bessel_J1(kr)/kr;
}

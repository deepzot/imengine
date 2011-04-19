// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/ExponentialProfile.h"
#include "imengine/InvalidValue.h"

#include <cmath>

namespace local = imengine::models;

local::ExponentialProfile::ExponentialProfile(double alpha) :
_twopi(8*std::atan(1.0))
{
    setParameters(alpha);
}

void local::ExponentialProfile::setParameters(double alpha) {
    if(isInitialized() && alpha == _a) return;
    assertGreaterThan<double>("ExponentialProfile alpha",alpha,0);
    _a = alpha;
    _a2 = _a*_a;
    _a3 = _a2*_a;
    _norm = _twopi/_a2;
    setChanged();
}

local::ExponentialProfile::~ExponentialProfile() { }

double local::ExponentialProfile::operator()(double r) const {
    return std::exp(-_a*r)/_norm;
}

double local::ExponentialProfile::radialIntegral(double kappa) const {
    return _a3*std::pow(_a2+kappa*kappa,-1.5);
}

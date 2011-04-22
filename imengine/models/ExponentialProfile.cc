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
    if(isInitialized() && alpha == _alpha) return;
    assertGreaterThan<double>("ExponentialProfile alpha",alpha,0);
    _alpha = alpha;
    _norm = _twopi*_alpha*_alpha;
    setChanged();
}

local::ExponentialProfile::~ExponentialProfile() { }

double local::ExponentialProfile::operator()(double r) const {
    return std::exp(-r/_alpha)/_norm;
}

double local::ExponentialProfile::radialIntegral(double kappa) const {
    double ak(_alpha*kappa);
    return std::pow(1+ak*ak,-1.5);
}

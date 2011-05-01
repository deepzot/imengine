// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/ExponentialProfile.h"
#include "imengine/InvalidValue.h"

#include <cmath>

namespace local = imengine::models;

local::ExponentialProfile::ExponentialProfile(double re) :
_twopi(8*std::atan(1.0))
{
    setParameters(re);
}

void local::ExponentialProfile::setParameters(double re) {
    if(isInitialized() && re == _re) return;
    assertGreaterThan<double>("ExponentialProfile re",re,0);
    _re = re;
    _alpha = _re/k;
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

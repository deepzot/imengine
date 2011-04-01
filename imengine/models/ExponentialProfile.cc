// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/ExponentialProfile.h"
#include "imengine/InvalidValue.h"

#include <cmath>

namespace local = imengine::models;

local::ExponentialProfile::ExponentialProfile(double alpha) :
_a(alpha),_a2(alpha*alpha), _a3(alpha*alpha*alpha)
{
    assertGreaterThan<double>("ExponentialProfile alpha",_a,0);
    double twopi(8*std::atan(1.0));
    double _norm(twopi/_a2);
}

local::ExponentialProfile::~ExponentialProfile() { }

double local::ExponentialProfile::operator()(double r) const {
    return _norm*std::exp(-_a*r);
}

double local::ExponentialProfile::radialIntegral(double kappa) const {
    return _a3*std::pow(_a2+kappa*kappa,-1.5);
}

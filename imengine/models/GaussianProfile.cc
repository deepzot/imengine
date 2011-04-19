// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/GaussianProfile.h"
#include "imengine/InvalidValue.h"

#include <cmath>

namespace local = imengine::models;

local::GaussianProfile::GaussianProfile(double sigma)
: _twopi(8*std::atan(1.0))
{
    setParameters(sigma);
}

void local::GaussianProfile::setParameters(double sigma) {
    if(isInitialized() && sigma == _sigma) return;
    assertGreaterThan<double>("GaussianProfile sigma",sigma,0);
    _sigma = sigma;
    double sigsq(sigma*sigma);
    _twosigsq = sigsq*2;
    _sigsqby2 = sigsq/2;
    _norm = 1/(_twopi*sigsq);
    setChanged();
}

local::GaussianProfile::~GaussianProfile() {
}

double local::GaussianProfile::operator()(double r) const {
    return _norm*std::exp(-r*r/_twosigsq);
}

double local::GaussianProfile::radialIntegral(double kappa) const {
    return std::exp(-kappa*kappa*_sigsqby2);
}

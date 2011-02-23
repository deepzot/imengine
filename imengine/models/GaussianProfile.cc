// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/GaussianProfile.h"

#include <iostream>
#include <cassert>
#include <cmath>

namespace local = imengine::models;

local::GaussianProfile::GaussianProfile(double sigma) {
    assert(sigma > 0);
    _twosigsq = 2*sigma*sigma;
    _sigsqby2 = _twosigsq/4;
    double root2pi(std::sqrt(8*std::atan(1.0)));
    _norm = 1/(root2pi*sigma);
    _integralNorm = sigma/root2pi;
}

local::GaussianProfile::~GaussianProfile() {
    std::cout << "GaussianProfile::dtor says bye" << std::endl;
}

double local::GaussianProfile::operator()(double r) const {
    return _norm*std::exp(-r*r/_twosigsq);
}

double local::GaussianProfile::radialIntegral(double kappa) const {
    return _integralNorm*std::exp(-kappa*kappa*_sigsqby2);
}
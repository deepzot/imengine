// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/GaussianProfile.h"

#include <iostream>
#include <cassert>
#include <cmath>

namespace local = imengine::models;

local::GaussianProfile::GaussianProfile(double sigma) {
    assert(sigma > 0);
    double sigsq(sigma*sigma);
    _twosigsq = sigsq*2;
    _sigsqby2 = sigsq/2;
    double twopi(8*std::atan(1.0));
    _norm = 1/(twopi*sigsq);
}

local::GaussianProfile::~GaussianProfile() {
    std::cout << "GaussianProfile::dtor says bye" << std::endl;
}

double local::GaussianProfile::operator()(double r) const {
    return _norm*std::exp(-r*r/_twosigsq);
}

double local::GaussianProfile::radialIntegral(double kappa) const {
    return std::exp(-kappa*kappa*_sigsqby2);
}
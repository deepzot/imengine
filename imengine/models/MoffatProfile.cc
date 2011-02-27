// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/MoffatProfile.h"

#include <cassert>
#include <cmath>

#include "boost/math/special_functions.hpp"

namespace local = imengine::models;

local::MoffatProfile::MoffatProfile(double fwhm, double beta) :
_beta(beta),_nu(1-beta)
{
    assert(fwhm > 0);
    assert(beta > 1);
    _rd = fwhm/(2*std::sqrt(std::pow(2,1/beta)-1));
    double pi(4*std::atan(1.0));
    _norm = (beta-1)/(pi*_rd*_rd);
    _integralNorm = (beta-1)*std::pow(2,2-beta)/boost::math::tgamma(beta);
}

local::MoffatProfile::~MoffatProfile() { }

double local::MoffatProfile::operator()(double r) const {
    double ratio(r/_rd);
    return _norm*std::pow(1+ratio*ratio,-_beta);
}

double local::MoffatProfile::radialIntegral(double kappa) const {
    double kr(kappa*_rd);
    return _integralNorm*std::pow(kr,_beta-1)*boost::math::cyl_bessel_k(_nu,kr);
}
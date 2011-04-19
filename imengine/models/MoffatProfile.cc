// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/MoffatProfile.h"
#include "imengine/InvalidValue.h"

#include <cmath>

#include "boost/math/special_functions.hpp"

namespace local = imengine::models;

local::MoffatProfile::MoffatProfile(double fwhm, double beta) :
_pi(4*std::atan(1.0))
{
    _rootpiby3 = std::sqrt(_pi)/3;
    setParameters(fwhm,beta);
}

local::MoffatProfile::~MoffatProfile() { }

void local::MoffatProfile::setParameters(double fwhm, double beta) {
    if(isInitialized() && fwhm == _fwhm && beta == _beta) return;
    assertGreaterThan<double>("MoffatProfile beta",beta,1);
    assertGreaterThan<double>("MoffateProfile fwhm",fwhm,0);
    _fwhm = fwhm;
    _beta = beta;
    _nu = 1 - beta;
    _rd = fwhm/(2*std::sqrt(std::pow(2,1/beta)-1));
    _norm = (beta-1)/(_pi*_rd*_rd);
    _integralNorm = 2*(beta-1)/boost::math::tgamma(beta);
    _approxNorm = _integralNorm*_rootpiby3*std::pow(2,-beta-9.5);
    double b2(beta*beta),b3(beta*b2),b4(b2*b2),b5(b3*b2),b6(b4*b2);
    _p0 = 315 - 216*beta - 1364*b2 + 960*b3 + 400*b4 - 384*b5 + 64*b6;
    _p1 = -360*beta + 384*b2 + 1344*b3 - 1536*b4 + 384*b5;
    _p2 = 1152*b2 - 3072*b3 + 1536*b4;
    _p3 = 3072*b3;
    setChanged();
}

double local::MoffatProfile::operator()(double r) const {
    double ratio(r/_rd);
    return _norm*std::pow(1+ratio*ratio,-_beta);
}

double local::MoffatProfile::radialIntegral(double kappa) const {
    if(0 == kappa) return 1;
    double result,kr(kappa*_rd);
    if(kr < 2.5*_beta || _beta > 7) {
        // Use the exact (but expensive) result
        result = _integralNorm/std::pow(kr/2,_nu)*boost::math::cyl_bessel_k(_nu,kr);
    }
    else {
        // use a 5th order asymptotic approximation that is accurate at 1%
        // for beta < 7 and at 0.05% for beta < 5.
        double x(kr/_beta);
        double poly(_p0 + x*(_p1 + x*(_p2 + x*_p3)));
        result = _approxNorm*std::pow(kr,_beta-4.5)*std::exp(-kr)*poly;
    }
    return result;
}

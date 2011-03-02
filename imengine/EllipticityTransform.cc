// Created 26-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/EllipticityTransform.h"

#include <cmath>
#include <cassert>
#include <iostream>

namespace local = imengine;

local::EllipticityTransform::EllipticityTransform(double e1, double e2) :
_e1p(1+e1),_e1m(1-e1),_e2(e2)
{
    _detM = 1 - e1*e1 - e2*e2;
    assert(0 < _detM);
    std::cout << "EllipticityTransform(" << e1 << ',' << e2 << ')' << std::endl;
}

local::EllipticityTransform::~EllipticityTransform() {
    std::cout << "EllipticityTransform::dtor" << std::endl;
}

double local::EllipticityTransform::determinant() const {
    return _detM;
}

double local::EllipticityTransform::transformedRadius(double x, double y) const {
    double xp(_e1m*x - _e2*y);
    double yp(_e1p*y - _e2*x);
    return std::sqrt(xp*xp + yp*yp);
}

double local::EllipticityTransform::transformedWaveNumber(double kx, double ky) const {
    double kxp(_e1p*kx + _e2*ky);
    double kyp(_e1m*ky + _e2*kx);
    return std::sqrt(kxp*kxp + kyp*kyp)/_detM;
}
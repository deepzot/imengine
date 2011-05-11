// Created 26-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/EllipticityTransform.h"
#include "imengine/InvalidValue.h"

#include <cmath>

namespace local = imengine;

local::EllipticityTransform::EllipticityTransform(double e1, double e2, double g1, double g2)
{
    setParameters(e1,e2,g1,g2);
}

local::EllipticityTransform::~EllipticityTransform() {
}

void local::EllipticityTransform::setParameters(double e1, double e2, double g1, double g2) {
    if(isInitialized() && e1 == _e1 && e2 == _e2 && g1 == _g1 && g2 == _g2) return;
    _e1 = e1;
    _e2 = e2;
    _g1 = g1;
    _g2 = g2;
    // Calculate the 2x2 matrix elements of M = {{a,b},{c,d}}
    _a = (1-e1)*(1-g1) + e2*g2;
    _b = -e2*(1+g1) - g2*(1-e1);
    _c = -e2*(1-g1) - g2*(1+e1);
    _d = (1+e1)*(1+g1) + e2*g2;
    _detM = _a*_d - _b*_c; // = (1 - e1*e1 - e2*e2)*(1 - g1*g1 - g2*g2)
    assertGreaterThan<double>("EllipticityTransform det(M)",_detM,0);
    setChanged();
}

double local::EllipticityTransform::determinant() const {
    return _detM;
}

double local::EllipticityTransform::transformedRadius(double x, double y) const {
    double xp(_a*x + _b*y);
    double yp(_c*x + _d*y);
    return std::sqrt(xp*xp + yp*yp);
}

double local::EllipticityTransform::transformedWaveNumber(double kx, double ky) const {
    double kxp(_d*kx - _c*ky);
    double kyp(_a*ky - _b*kx);
    return std::sqrt(kxp*kxp + kyp*kyp)/_detM;
}

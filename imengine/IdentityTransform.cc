// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/IdentityTransform.h"

#include <cmath>

namespace local = imengine;

local::IdentityTransform::IdentityTransform() { }

local::IdentityTransform::~IdentityTransform() { }

double local::IdentityTransform::determinant() const {
    return 1;
}

double local::IdentityTransform::transformedRadius(double x, double y) const {
    return std::sqrt(x*x + y*y);
}

double local::IdentityTransform::transformedWaveNumber(double kx, double ky) const {
    return std::sqrt(kx*kx + ky*ky);
}
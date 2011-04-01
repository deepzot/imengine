// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/GaussianDemo.h"
#include "imengine/InvalidValue.h"

#include <cmath>

namespace local = imengine::models;

local::GaussianDemo::GaussianDemo(double sigma) :
GenericPixelFunction(), _sigma(sigma)
{
    assertGreaterThan<double>("GaussianDemo sigma",_sigma,0);
    double sigsq(sigma*sigma);
    _twosigmasq = 2*sigsq;
    double twopi(8*std::atan(1.0));
    _norm = twopi*sigsq;
}

local::GaussianDemo::~GaussianDemo() { }

double local::GaussianDemo::operator()(double x, double y) const {
    double rsq = x*x + y*y;
    return std::exp(-rsq/_twosigmasq)/_norm;
}

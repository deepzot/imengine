// Created 17-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/SersicDemo.h"
#include "imengine/InvalidValue.h"

#include "boost/math/special_functions.hpp"

#include <cmath>

namespace local = imengine::models;

local::SersicDemo::SersicDemo(double alpha, double index)
: _alpha(alpha), _index(index)
{
    assertGreaterThan<double>("SersicDemo alpha",_alpha,0);
    assertGreaterThan<double>("SersicDemo index",_index,0);
    double twopi(8*std::atan(1.0));
    _norm = twopi*_index*std::pow(_alpha,-2*_index)*boost::math::tgamma(2*_index);
}

local::SersicDemo::~SersicDemo() { }

double local::SersicDemo::operator()(double x, double y) const {
    double rsq(x*x + y*y);
    return std::exp(-_alpha*std::pow(rsq,1/(2*_index)))/_norm;
}

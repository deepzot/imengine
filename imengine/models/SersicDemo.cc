// Created 17-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/SersicDemo.h"
#include "imengine/InvalidValue.h"

#include "boost/math/special_functions.hpp"

#include <cmath>

namespace local = imengine::models;

local::SersicDemo::SersicDemo(double alpha, double index, double e1, double e2)
: _initialized(false), _twopi(8*std::atan(1.0)), _alpha(0), _index(0), _transform(e1,e2)
{
    _transform.setObserver(getObserver());
    setParameters(alpha, index, e1, e2);
}

local::SersicDemo::~SersicDemo() { }

void local::SersicDemo::setParameters(double alpha, double index, double e1, double e2) {
    _transform.setParameters(e1,e2);
    if(_initialized && alpha == _alpha && index == _index) return;
    assertGreaterThan<double>("SersicDemo alpha",alpha,0);
    assertGreaterThan<double>("SersicDemo index",index,0);
    _alpha = alpha;
    _index = index;
    _inverseIndex = 1/_index;
    _norm = _twopi*_index*std::pow(_alpha,-2*_index)*
        boost::math::tgamma(2*_index)/_transform.determinant();
    _initialized = true;
    setChanged();
}

double local::SersicDemo::operator()(double x, double y) const {
    double r(_transform.transformedRadius(x,y));
    return std::exp(-_alpha*std::pow(r,_inverseIndex))/_norm;
}

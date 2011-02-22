// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformedProfileFunction.h"
#include "imengine/AbsRadialProfile.h"
#include "imengine/AbsCoordTransform.h"

#include "boost/bind.hpp"

#include <cassert>

namespace local = imengine;

local::TransformedProfileFunction::TransformedProfileFunction(
AbsRadialProfile const &profile, AbsCoordTransform &transform) :
_radialProfile(profile), _coordTransform(transform)
{        
}

local::TransformedProfileFunction::~TransformedProfileFunction() { }

double local::TransformedProfileFunction::operator()(double x, double y) const {
    double r(_coordTransform.transformedRadius(x,y));
    return _radialProfile.evaluate(r);
}

void local::TransformedProfileFunction::initTransform(TransformData* transformData) {
    assert(0 != transformData);
    _transformData = transformData;
}

void local::TransformedProfileFunction::doTransform() {
    _transformData->tabulate(boost::bind(&local::TransformedProfileFunction::tabulator,this));
}

void local::TransformedProfileFunction::tabulator(double kx, double ky,
local::TransformData::Complex& value) {
    double kappa(_coordTransform.transformedWaveNumber(kx,ky));
    value[0] = _radialProfile.radialIntegral(kappa);
    value[1] = 0;
}
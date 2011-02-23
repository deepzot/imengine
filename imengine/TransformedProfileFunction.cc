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
    _determinant = _coordTransform.determinant();
    assert(0 < _determinant);
}

local::TransformedProfileFunction::~TransformedProfileFunction() { }

double local::TransformedProfileFunction::operator()(double x, double y) const {
    double r(_coordTransform.transformedRadius(x,y));
    return _radialProfile(r);
}

void local::TransformedProfileFunction::initTransform(TransformData* transformData) {
    assert(0 != transformData);
    _transformData = transformData;
}

void local::TransformedProfileFunction::doTransform() {
    _transformData->tabulate(
        boost::bind(&local::TransformedProfileFunction::tabulator,this,_1,_2,_3));
}

void local::TransformedProfileFunction::tabulator(double kx, double ky,
local::TransformData::Complex& value) {
    double kappa(_coordTransform.transformedWaveNumber(kx,ky));
    value[0] = _radialProfile.radialIntegral(kappa)/_determinant;
    value[1] = 0;
}
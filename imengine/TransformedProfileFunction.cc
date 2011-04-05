// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformedProfileFunction.h"
#include "imengine/AbsRadialProfile.h"
#include "imengine/AbsCoordTransform.h"
#include "imengine/TransformData.h"
#include "imengine/RuntimeError.h"

#include "boost/bind.hpp"

namespace local = imengine;

local::TransformedProfileFunction::TransformedProfileFunction(
AbsRadialProfilePtr profile,AbsCoordTransformPtr transform) :
_radialProfile(profile), _coordTransform(transform)
{
    // check that we have real live workers
    if(0 == _radialProfile.get()) {
        throw RuntimeError("TransformedProfileFunction needs a radial profile.");
    }
    if(0 == _coordTransform.get()) {
        throw RuntimeError("TransformedProfileFunction needs a coordinate transform.");
    }
    // delegate observing duties to our workers
    _radialProfile->setObserver(getObserver());
    _coordTransform->setObserver(getObserver());
}

local::TransformedProfileFunction::~TransformedProfileFunction() {
}

double local::TransformedProfileFunction::operator()(double x, double y) const {
    double r(_coordTransform->transformedRadius(x,y));
    return (*_radialProfile)(r);
}

void local::TransformedProfileFunction::doTransform(TransformDataPtr transformData) {
    transformData->tabulate(
        boost::bind(&local::TransformedProfileFunction::tabulator,this,_1,_2,_3));
}

void local::TransformedProfileFunction::tabulator(double kx, double ky, local::Complex& value) {
    double kappa(_coordTransform->transformedWaveNumber(kx,ky));
    value[0] = _radialProfile->radialIntegral(kappa);
    value[1] = 0;
}
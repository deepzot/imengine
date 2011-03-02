// Created 22-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformedProfileFunction.h"
#include "imengine/AbsRadialProfile.h"
#include "imengine/AbsCoordTransform.h"
#include "imengine/TransformData.h"

#include "boost/bind.hpp"

#include <cassert>
#include <iostream>

namespace local = imengine;

local::TransformedProfileFunction::TransformedProfileFunction(
boost::shared_ptr<AbsRadialProfile const> profile,
boost::shared_ptr<AbsCoordTransform const> transform) :
_radialProfile(profile), _coordTransform(transform)
{
    //std::cout << "TransformedProfileFunction(...)" << std::endl;
}

local::TransformedProfileFunction::~TransformedProfileFunction() {
    //std::cout << "TransformedProfileFunction::dtor" << std::endl;
}

double local::TransformedProfileFunction::operator()(double x, double y) const {
    double r(_coordTransform->transformedRadius(x,y));
    return (*_radialProfile)(r);
}

void local::TransformedProfileFunction::doTransform(
boost::shared_ptr<TransformData> transformData) {
    transformData->tabulate(
        boost::bind(&local::TransformedProfileFunction::tabulator,this,_1,_2,_3));
}

void local::TransformedProfileFunction::tabulator(double kx, double ky, local::Complex& value) {
    double kappa(_coordTransform->transformedWaveNumber(kx,ky));
    value[0] = _radialProfile->radialIntegral(kappa);
    value[1] = 0;
}
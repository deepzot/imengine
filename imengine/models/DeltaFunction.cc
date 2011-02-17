// Created 17-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/DeltaFunction.h"

#include <cassert>

namespace local = imengine::models;

local::DeltaFunction::DeltaFunction() { }

local::DeltaFunction::~DeltaFunction() { }

void local::DeltaFunction::initTransform(TransformData* transformData) {
    assert(0 != transformData);
    _transformData = transformData;
}

void local::DeltaFunction::doTransform() {
    _transformData->tabulate(&local::DeltaFunction::setValueToOne);
}

double local::DeltaFunction::operator()(double x, double y) const {
    return 0;
}

void local::DeltaFunction::setValueToOne(double kx, double ky, imengine::TransformData::Complex& value) {
    value[0] = 1;
    value[1] = 0;
}
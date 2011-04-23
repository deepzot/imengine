// Created 22-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/PixelFunctionSum.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/TransformData.h"
#include "imengine/InvalidValue.h"

namespace local = imengine;

local::PixelFunctionSum::PixelFunctionSum(
AbsPixelFunctionPtr f1, AbsPixelFunctionPtr f2, double frac1, double dx, double dy)
: _f1(f1), _f2(f2), _initialized(false)
{
    setParameters(frac1,dx,dy);
}

local::PixelFunctionSum::~PixelFunctionSum() { }

void local::PixelFunctionSum::setParameters(double frac1, double dx, double dy) {
    if(_initialized && _frac1 == frac1 && _dx == dx && _dy == dy) return;
    assertGreaterThanOrEqualTo<double>("PixelFunctionSum frac1",frac1,0);
    assertLessThanOrEqualTo<double>("PixelFunctionSum frac1",frac1,1);
    _frac1 = frac1;
    _dx = dx;
    _dy = dy;
    _initialized = true;
    setChanged();
}

double local::PixelFunctionSum::operator()(double x, double y) const {
    return _frac1*_f1->operator()(x,y) + (1-_frac1)*_f2->operator()(x-_dx,y-_dy);
}

void local::PixelFunctionSum::initTransform(TransformDataPtr transformData) {
    // allocate transform data arrays for f1,f2 by cloning the input parameter
    _transform1 = transformData->clone();
    _transform2 = transformData->clone();
    // initialize f1,f2 with their new transform data arrays
    _f1->initTransform(_transform1);
    _f2->initTransform(_transform2);
    // base class initialization
    AbsPixelFunction::initTransform(transformData);
}

void local::PixelFunctionSum::doTransform(TransformDataPtr transformData) {
    // update the transforms if necessary
    if(_f1->hasChanged()) _f1->computeTransform(_transform1);
    if(_f2->hasChanged()) _f2->computeTransform(_transform2);
    // fill the provided transform with the scaled sum
    transformData->setToSum(_transform1,_transform2,_frac1,1-_frac1,_dx,_dy);
}

bool local::PixelFunctionSum::hasChanged() const {
    return AbsPixelFunction::hasChanged() || _f1->hasChanged() || _f2->hasChanged();
}
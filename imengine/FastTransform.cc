// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/FastTransform.h"
#include "imengine/InterpolationData.h"

namespace local = imengine;

local::FastTransform::FastTransform(InterpolationData &target)
: TransformData(target), _forwardPlan(0), _inversePlan(0)
{
}

local::FastTransform::~FastTransform() {
    if(0 != _forwardPlan) fftw_destroy_plan(_forwardPlan);
    if(0 != _inversePlan) fftw_destroy_plan(_inversePlan);
}

void local::FastTransform::setToTransform() {
    if(0 == _forwardPlan) {
        _forwardPlan = fftw_plan_dft_r2c_2d(_gridSize,_gridSize,
            getTargetDataPtr(),(fftw_complex*)getDataPtr(),FFTW_ESTIMATE);
    }
}

void local::FastTransform::inverseTransform() {
}
// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/FastTransform.h"
#include "imengine/InterpolationData.h"
#include "imengine/fftw.h"

namespace local = imengine;

local::FastTransform::FastTransform(boost::shared_ptr<InterpolationData> target)
: TransformData(target), _forwardPlan(0), _inversePlan(0)
{
    int strategy = FFTW_MEASURE; // FFTW_ESTIMATE
    _forwardPlan = FFTW(plan_dft_r2c_2d)(_gridSize,_gridSize,
        getTargetDataPtr(),(FFTW(complex)*)getDataPtr(),strategy);
    _inversePlan = FFTW(plan_dft_c2r_2d)(_gridSize,_gridSize,
        (FFTW(complex)*)getDataPtr(),getTargetDataPtr(),strategy);
}

local::FastTransform::~FastTransform() {
    if(0 != _forwardPlan) FFTW(destroy_plan)((FFTW(plan))_forwardPlan);
    if(0 != _inversePlan) FFTW(destroy_plan)((FFTW(plan))_inversePlan);
}

void local::FastTransform::setToTransform() {
    FFTW(execute)((FFTW(plan))_forwardPlan);
}

void local::FastTransform::inverseTransform() {
    FFTW(execute)((FFTW(plan))_inversePlan);
}

local::TransformDataPtr local::FastTransform::clone() const {
    TransformDataPtr _clone;
    return _clone;
}
// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/SlowTransform.h"
#include "imengine/InterpolationData.h"

#include <cmath>

namespace local = imengine;

local::SlowTransform::SlowTransform(InterpolationData &target)
: TransformData(target)
{
}

local::SlowTransform::~SlowTransform() { }

void local::SlowTransform::inverseTransform() {
    int N(_gridSize);
    double dtheta = +8*std::atan(1.0)/N; // +2pi/N
    for(int j = 0; j < N; j++) {
        for(int i = 0; i < N; i++) {
            double value(0);
            for(int n = 0; n < N; n++) {
                for(int m = 0; m < N; m++) {
                    double theta = dtheta*(m*i + n*j);
                    value += getReal(m,n)*std::cos(theta) - getImag(m,n)*std::sin(theta);
                }
            }
            setTargetValue(i,j,value);
        }
    }
}

void local::SlowTransform::setToTransform() {
    double dtheta = -8*std::atan(1.0)/_gridSize; // -2pi/N
    for(int j = 0; j < _gridSize; j++) {
        for(int i = 0; i < _break1; i++) {
            double re(0), im(0);
            for(int n = 0; n < _gridSize; n++) {
                for(int m = 0; m < _gridSize; m++) {
                    double value = getTarget().getValue(m,n);
                    double theta = dtheta*(m*i + n*j);
                    re += value*std::cos(theta);
                    im += value*std::sin(theta);
                }
            }
            real(i,j) = re;
            imag(i,j) = im;
        }
    }
}


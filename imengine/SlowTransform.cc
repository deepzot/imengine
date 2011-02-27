// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/SlowTransform.h"
#include "imengine/InterpolationData.h"

#include <cmath>

namespace local = imengine;

local::SlowTransform::SlowTransform(boost::shared_ptr<InterpolationData> target)
: TransformData(target)
{
}

local::SlowTransform::~SlowTransform() { }

void local::SlowTransform::inverseTransform() {
    int N(_gridSize);
    double dtheta = +8*std::atan(1.0)/N; // +2pi/N
    for(int j = 0; j < N; j++) {
        for(int i = 0; i < N; i++) {
            double re(0),im(0);
            for(int n = 0; n < N; n++) {
                for(int m = 0; m < N; m++) {
                    double re1(getReal(m,n)),im1(getImag(m,n));
                    double theta = dtheta*(m*i + n*j);
                    double re2(std::cos(theta)),im2(std::sin(theta));
                    re += re1*re2 - im1*im2;
                    //im += re1*im2 + re2*im1;
                }
            }
            setTargetValue(i,j,re);
            //assert(std::fabs(im) < 1e-8);
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
                    double value = getTargetValue(m,n);
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


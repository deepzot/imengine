// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/TransformData.h"

#include <cassert>
#include <cmath>
#include <iostream>

namespace local = imengine;

local::TransformData::TransformData(int gridSize, double gridSpacing) :
DataGrid(gridSize,gridSpacing)
{
    double twopi = 8*std::atan(1.0);
    _dk = twopi/(gridSize*gridSpacing);
    _norm = 1.0/(gridSize*gridSize);
    _data = new double[2*gridSize*gridSize];
}

local::TransformData::~TransformData() {
    delete[] _data;
}

void local::TransformData::setToProduct(local::TransformData const& t1, local::TransformData const& t2,
double dx, double dy) {
    // is there any translation to apply?
    bool translated = (0 != dx)||(0 != dy);
    double norm = _gridSpacing*_gridSpacing;
    for(int j = 0; j < _gridSize; j++) {
        for(int i = 0; i < _gridSize; i++) {
            double re1(t1.real(i,j)),im1(t1.imag(i,j)),re2(t2.real(i,j)),im2(t2.imag(i,j));
            double re = norm*(re1*re2 - im1*im2);
            double im = norm*(re1*im2 + im1*re2);
            if(translated) {
                double theta = -(waveNumber(i)*dx + waveNumber(j)*dy);
                double costh = std::cos(theta);
                double sinth = std::sin(theta);
                real(i,j) = re*costh - im*sinth;
                imag(i,j) = re*sinth + im*costh;
            }
            else {
                real(i,j) = re;
                imag(i,j) = im;
            }
        }
    }
}

void local::TransformData::dumpAbsSquared() const {
    for(int j = 0; j < _gridSize; j++) {
        for(int i = 0; i < _gridSize; i++) {
            std::cout << absSquared(i,j) << ' ';
        }
        std::cout << std::endl;
    }
}

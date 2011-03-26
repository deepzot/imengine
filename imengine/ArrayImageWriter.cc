// Created 23-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ArrayImageWriter.h"

#include <cassert>
#include <iostream>
#include <cmath>

namespace local = imengine;

local::ArrayImageWriter::ArrayImageWriter()
: AbsImageWriter(), _data(0), _size(0)
{
}

local::ArrayImageWriter::~ArrayImageWriter() { }

void local::ArrayImageWriter::open(int size, double scale) {
    assert(size > 0);
    // re-allocate the array from a previous image if it was a different size
    if(_size == 0 || size != _size) {
        _data.reset(new double[size*size]);
    }
    _size = size;
}

double local::ArrayImageWriter::write(int x, int y, double value) {
    _data[x + y*_size] = value;
    return value;
}

void local::ArrayImageWriter::close() { }

double local::ArrayImageWriter::getValue(int x, int y) const {
    return (0 != _data) ? _data[x + y*_size] : 0;
}

bool local::compareImages(ArrayImageWriter const &first, ArrayImageWriter const &second,
bool verbose, double abstol, double reltol)
{
    if(first.getSize() != second.getSize()) {
        if(verbose) {
            std::cout << "compareImages: sizes do not match! " << first.getSize()
                << ", " << second.getSize() << std::endl;
        }
        return false;
    }
    int N(first.getSize());
    bool pass(true);
    double maxDelta(0),maxFrac(0);
    for(int x = 0; x < N; x++) {
        for(int y = 0; y < N; y++) {
            double value1 = first.getValue(x,y);
            double value2 = second.getValue(x,y);
            double delta = std::fabs(value1 - value2);
            double sum = std::fabs(value1 + value2);
            if(delta > maxDelta) {
                maxDelta = delta;
            }
            if(delta > abstol) {
                if(false && verbose) {
                    std::cout << "compareImages: |v1-v2| > " << abstol << " at (x,y) = ("
                        << x << ',' << y << ")" << std::endl;
                }
                pass = false;
            }
            if(sum > 0) {
                double frac = delta/sum;
                if(frac > maxFrac) {
                    maxFrac = frac;
                }
                if(frac > reltol) {
                    if(false && verbose) {
                        std::cout << "compareImages: |v1-v2|/|v1+v2| > " << reltol
                            << " at (x,y) = (" << x << ',' << y << ")" << std::endl;
                    }
                    pass = false;                
                }
            }
        }
    }
    if(verbose) {
        std::cout << "compareImages: max|v1-v2| = " << maxDelta << " , max|v1-v2|/|v1+v2| = "
            << maxFrac << std::endl;
    }
    return pass;
}

// Created 25-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/OversamplingImageEngine.h"
#include "imengine/ArrayImageWriter.h"

#include <cassert>

namespace local = imengine;

local::OversamplingImageEngine::OversamplingImageEngine(AbsImageEnginePtr engine, int subpixels)
: _subpixelData(new ArrayImageWriter()), _engine(engine), _subpixels(subpixels)
{
    assert(0 != _engine.get());
    assert(_subpixels >= 1);
}

local::OversamplingImageEngine::~OversamplingImageEngine() { }

void local::OversamplingImageEngine::initialize(int pixelsPerSide, double pixelScale) {
    AbsImageEngine::initialize(pixelsPerSide,pixelScale);
    _engine->initialize(_subpixels*pixelsPerSide, pixelScale/_subpixels);
}

double local::OversamplingImageEngine::generate(AbsImageWriter &writer, double dx, double dy) {
    // initialize the writer
    writer.open(getPixelsPerSide(),getPixelScale());
    // use the engine to calculate oversampled data
    double sum(_engine->generate(*_subpixelData,dx,dy));
    // downsample to the final pixels
    int N(_subpixelData->getSize());
    /**
    for(int y = 0; y < N; ++y) {
        for(int x = 0; x < N; ++x) {
            std::cout << ' ' << _subpixelData->getValue(x,y);
        }
        std::cout << std::endl;
    }
    **/
    for(int y = 0; y < N; y += _subpixels) {
        for(int x = 0; x < N; x += _subpixels) {
            double value(0);
            for(int dy = 0; dy < _subpixels; ++dy) {
                for(int dx = 0; dx < _subpixels; ++dx) {
                    value += _subpixelData->getValue(x+dx,y+dy);
                }
            }
            writer.write(x/_subpixels,y/_subpixels,value);
        }
    }
    writer.close();
    return sum;
}
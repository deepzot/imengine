// Created 19-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ResizingImageEngine.h"
#include "imengine/ArrayImageWriter.h"
#include "imengine/InvalidValue.h"

#include <cassert>

namespace local = imengine;

local::ResizingImageEngine::ResizingImageEngine(AbsImageEnginePtr engine, int pixelMargin)
: _generatedPixelData(new ArrayImageWriter()), _engine(engine), _pixelMargin(pixelMargin)
{
    assert(0 != _engine.get());
}

local::ResizingImageEngine::~ResizingImageEngine() { }

void local::ResizingImageEngine::initialize(int pixelsPerSide, double pixelScale) {
    AbsImageEngine::initialize(pixelsPerSide,pixelScale);
    int genPixelsPerSide(pixelsPerSide + 2*_pixelMargin);
    assertGreaterThanOrEqualTo<int>("ResizingImageEngine generated pixels per side",
        genPixelsPerSide,1);
    _engine->initialize(genPixelsPerSide, pixelScale);
}

double local::ResizingImageEngine::generate(AbsImageWriter &writer, double dx, double dy) {
    // initialize the writer
    int Nfinal(getPixelsPerSide());
    writer.open(Nfinal,getPixelScale());
    // use the engine to calculate oversampled data
    double generatedSum(_engine->generate(*_generatedPixelData,dx,dy));
    // resize to the final pixels
    double finalSum(0);
    int Ngen(_generatedPixelData->getSize());
    for(int y = 0; y < Nfinal; ++y) {
        int ygen(y + _pixelMargin);
        for(int x = 0; x < Nfinal; ++x) {
            int xgen(x + _pixelMargin);
            double value(0);
            // do we have generated data for this pixel?
            if(ygen >= 0 && xgen >= 0 && ygen < Ngen && xgen < Ngen) {
                value = _generatedPixelData->getValue(xgen,ygen);
            }
            writer.write(x,y,value);
            finalSum += value;
        }
    }
    writer.close();
    return finalSum;
}

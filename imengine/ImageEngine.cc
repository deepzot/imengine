// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ImageEngine.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/TransformData.h"

#include <cassert>

namespace local = imengine;

local::ImageEngine::ImageEngine(const local::AbsPixelFunction& source, 
const local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
_source(source), _psf(psf), _pixelsPerSide(pixelsPerSide), _pixelScale(pixelScale),
_sourceTransform(0), _psfTransform(0), _imageTransform(0)
{
    assert(pixelsPerSide > 0);
    assert(pixelScale > 0);
    // delegate the calculation of our transform grid parameters
    setGridParams();
    // allocate the transform data arrays
    _sourceTransform = new TransformData(gridSize,gridSpacing);
    _psfTransform = new TransformData(gridSize,gridSpacing);
    _imageTransform = new TransformData(gridSize,gridSpacing);
}

local::ImageEngine::~ImageEngine() {
    delete _sourceTransform;
    delete _psfTransform;
    delete _imageTransform;
}

local::ImageData *local::ImageEngine::generate(double dx, double dy) {
    return 0;
}

void local::ImageEngine::setGridParams() {
    // subclasses must override this method
    assert(0);
}
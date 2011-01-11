// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ImageEngine.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/TransformData.h"

#include <cassert>

namespace local = imengine;

local::ImageEngine::ImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
_source(source), _psf(psf), _pixelsPerSide(pixelsPerSide), _pixelScale(pixelScale),
_sourceTransform(0), _psfTransform(0), _imageTransform(0)
{
    assert(pixelsPerSide > 0);
    assert(pixelScale > 0);
}

local::ImageEngine::~ImageEngine() {
    if(0 != _sourceTransform) {
        delete _sourceTransform;
        delete _psfTransform;
        delete _imageTransform;
    }
}

local::ImageData *local::ImageEngine::generate(double dx, double dy) {
    // do one-time initialization of the transform grids
    if(0 == _imageTransform) {
        _imageTransform = createImageTransform();
        assert(0 != _imageTransform);
        // build source and psf transform grids with the same attributes
        _sourceTransform = TransformData::createFromPrototype(*_imageTransform);
        _psfTransform = TransformData::createFromPrototype(*_imageTransform);
        // link the grids to their pixel functions
        _source.initTransform(_sourceTransform);
        _psf.initTransform(_psfTransform);
    }
    return 0;
}

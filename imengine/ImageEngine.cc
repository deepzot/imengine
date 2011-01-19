// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ImageEngine.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/InterpolationData.h"
#include "imengine/TransformData.h"
#include "imengine/ImageWriter.h"

#include <cassert>

namespace local = imengine;

local::ImageEngine::ImageEngine(local::AbsPixelFunction& source, 
local::AbsPixelFunction& psf, int pixelsPerSide, double pixelScale) :
_source(source), _psf(psf), _pixelsPerSide(pixelsPerSide), _pixelScale(pixelScale),
_imageGrid(0), _sourceTransform(0), _psfTransform(0), _imageTransform(0)
{
    assert(pixelsPerSide > 0);
    assert(pixelScale > 0);
    _scaleSquared = pixelScale*pixelScale;
}

local::ImageEngine::~ImageEngine() {
    if(0 != _imageGrid) {
        delete _imageGrid;
        delete _sourceTransform;
        delete _psfTransform;
        delete _imageTransform;
    }
}

void local::ImageEngine::generate(local::ImageWriter &writer, double dx, double dy) {
    // do one-time initialization of the transform grids
    if(0 == _imageTransform) {
        _imageGrid = createGrid();
        assert(0 != _imageGrid);
        // build discrete Fourier transform grids with the same attributes but zero
        // out the offset in the psf otherwise it will be applied twice (an offset
        // in the image transform has no effect so we arbitrary zero it here)
        _sourceTransform = TransformData::createFromPrototype(*_imageGrid);
        _psfTransform = TransformData::createFromPrototype(*_imageGrid);
        _imageTransform = TransformData::createFromPrototype(*_imageGrid);
        // link the source and psf grids to their pixel functions
        _source.initTransform(_sourceTransform);
        _psf.initTransform(_psfTransform);
    }
    // calculate the discrete Fourier transform of the source and PSF (with any offset
    // only applied to the source)
    _source.doTransform(0,0);
    _psf.doTransform(0,0);
    // combine the source and PSF in Fourier space
    dx -= _imageGrid->getGridX();
    dy -= _imageGrid->getGridY();
    _imageTransform->setToProduct(*_sourceTransform,*_psfTransform,dx,dy);
    // build a grid of real-space convoluted image data
    _imageTransform->inverseTransform(*_imageGrid);
    // initialize our writer
    writer.open();
    // estimate the signal in each pixel
    for(int y = 0; y < _pixelsPerSide; y++) {
        for(int x = 0; x < _pixelsPerSide; x++) {
            writer.write(x,y,estimatePixelValue(x,y));
        }
    }
    writer.close();
}

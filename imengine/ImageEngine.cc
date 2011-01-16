// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ImageEngine.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/InterpolationData.h"
#include "imengine/TransformData.h"

#include <cassert>
#include <iostream>

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

void local::ImageEngine::generate(double dx, double dy) {
    // do one-time initialization of the transform grids
    if(0 == _imageTransform) {
        _imageGrid = createGrid();
        assert(0 != _imageGrid);
        // build discrete Fourier transform grids with the same attributes
        _imageTransform = TransformData::createFromPrototype(*_imageGrid);
        _sourceTransform = TransformData::createFromPrototype(*_imageGrid);
        _psfTransform = TransformData::createFromPrototype(*_imageGrid);
        // link the source and psf grids to their pixel functions
        _source.initTransform(_sourceTransform);
        _psf.initTransform(_psfTransform);
    }
    // calculate the discrete Fourier transform of the source and PSF
    double norm1 = _source.doTransform(dx,dy);
    double norm2 = _psf.doTransform(0,0);
    // combine the source and PSF in Fourier space
    _imageTransform->setToProduct(*_sourceTransform,*_psfTransform,norm1*norm2);
    // build a grid of real-space convoluted image data
    std::cout << "=== src ===" << std::endl;
    _sourceTransform->dumpAbsSquared();
    std::cout << "=== psf ===" << std::endl;
    _psfTransform->dumpAbsSquared();
    std::cout << "=== abs ===" << std::endl;
    _imageTransform->dumpAbsSquared();
    std::cout << "=== inv ===" << std::endl;
    _imageTransform->inverseTransform(*_imageGrid);
    _imageGrid->dump();
    std::cout << "===" << std::endl;
    // estimate the signal in each pixel
    for(int y = 0; y < _pixelsPerSide; y++) {
        for(int x = 0; x < _pixelsPerSide; x++) {
            double value = estimatePixelValue(x,y);
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }
}

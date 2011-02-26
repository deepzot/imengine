// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ImageEngine.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/InterpolationData.h"
#include "imengine/AbsImageWriter.h"

#include <cassert>
#include <iostream>

namespace local = imengine;

template <class T>
local::ImageEngine<T>::ImageEngine(local::AbsPixelFunction& source, local::AbsPixelFunction& psf)
: AbsImageEngine(source,psf),
_sourceTransform(0), _psfTransform(0), _imageTransform(0)
{
}

template <class T>
local::ImageEngine<T>::~ImageEngine() {
    if(0 != _imageTransform) {
        delete _sourceTransform;
        delete _psfTransform;
        delete _imageTransform;
    }
}

template <class T>
void local::ImageEngine<T>::initialize(int pixelsPerSide, double pixelScale) {
    AbsImageEngine::initialize(pixelsPerSide,pixelScale);
    _imageGrid = createGrid();
    assert(0 != _imageGrid);
    // create a private workspace with the same dimensions as the image grid
    _workspace = _imageGrid->createWorkspace();
    // build discrete Fourier transform grids (linked to the workspace) for
    // the source and psf models
    _sourceTransform = new T(*_workspace);
    _psfTransform = new T(*_workspace);
    // link the source and psf grids to their pixel functions
    _source.initTransform(_sourceTransform);
    _psf.initTransform(_psfTransform);
    // build a discrete Fourier transform grid for the final image
    _imageTransform = new T(*_imageGrid);
}

template <class T>
double local::ImageEngine<T>::generate(local::AbsImageWriter &writer, double dx, double dy) {
    assert(isInitialized());
    // calculate the discrete Fourier transform of the source and PSF (with any offset
    // only applied to the source)
    _source.doTransform();
    _psf.doTransform();
    // combine the source and PSF in Fourier space
    dx -= _imageGrid->getGridX();
    dy -= _imageGrid->getGridY();
    _imageTransform->setToProduct(*_sourceTransform,*_psfTransform,dx,dy);
    //_imageTransform->dump();
    // build a grid of real-space convoluted image data
    _imageTransform->inverseTransform();
    // initialize our writer
    int N(getPixelsPerSide());
    double sum(0);
    writer.open(N,getPixelScale());
    // estimate the signal in each pixel
    for(int y = 0; y < N; ++y) {
        for(int x = 0; x < N; ++x) {
            double value = estimatePixelValue(x,y);
            writer.write(x,y,value);
            sum += value;
        }
    }
    writer.close();
    return sum;
}

// explicit template instantiations

#include "imengine/SlowTransform.h"
template class local::ImageEngine<local::SlowTransform>;

#include "imengine/FastTransform.h"
template class local::ImageEngine<local::FastTransform>;
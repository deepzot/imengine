// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ImageEngine.h"
#include "imengine/AbsPixelFunction.h"
#include "imengine/InterpolationData.h"
#include "imengine/TransformData.h"
#include "imengine/AbsImageWriter.h"
#include "imengine/RuntimeError.h"

namespace local = imengine;

template <class T>
local::ImageEngine<T>::ImageEngine(AbsPixelFunctionPtr source, AbsPixelFunctionPtr psf)
: _source(source), _psf(psf), _validLast(false)
{
}

template <class T>
local::ImageEngine<T>::~ImageEngine() {
}

template <class T>
void local::ImageEngine<T>::initialize(int pixelsPerSide, double pixelScale) {
    AbsImageEngine::initialize(pixelsPerSide,pixelScale);
    _imageGrid.reset(createGrid());
    if(0 == _imageGrid.get()) {
        throw RuntimeError("createGrid() failed in ImageEngine::initialize");
    }
    // create a private workspace with the same dimensions as the image grid
    _workspace.reset(_imageGrid->createWorkspace());
    // build discrete Fourier transform grids (linked to the workspace) for
    // the source and psf models
    _sourceTransform.reset(new T(_workspace));
    _psfTransform.reset(new T(_workspace));
    // link the source and psf grids to their pixel functions
    _source->initTransform(_sourceTransform);
    _psf->initTransform(_psfTransform);
    // build a discrete Fourier transform grid for the final image
    _imageTransform.reset(new T(_imageGrid));
    // invalidate our last (dx,dy) values
    _validLast = false;
}

template <class T>
double local::ImageEngine<T>::generate(local::AbsImageWriter &writer, double dx, double dy) {
    if(!isInitialized()) {
        throw RuntimeError("ImageEngine must be initialized before generating.");
    }
    // calculate the discrete Fourier transform of the source and PSF (with any offset
    // only applied to the source)
    _source->computeTransform(_sourceTransform);
    _psf->computeTransform(_psfTransform);
    ////_psfTransform->dump();
    // combine the source and PSF in Fourier space
    dx -= _imageGrid->getGridX();
    dy -= _imageGrid->getGridY();
    _imageTransform->setToProduct(*_sourceTransform,*_psfTransform,dx,dy);
    ////_imageTransform->dump();
    // build a grid of real-space convoluted image data
    _imageTransform->inverseTransform();
    // initialize our writer
    int N(getPixelsPerSide());
    double sum(0);
    writer.open(N,getPixelScale());
    // estimate the signal in each pixel
    for(int y = 0; y < N; ++y) {
        for(int x = 0; x < N; ++x) {
            sum += writer.write(x,y,estimatePixelValue(x,y));
        }
    }
    writer.close();
    // remember these (dx,dy) values
    _lastDx = dx;
    _lastDy = dy;
    _validLast = true;
    // return the pixel sum of the generated image
    return sum;
}

// explicit template instantiations

#include "imengine/SlowTransform.h"
template class local::ImageEngine<local::SlowTransform>;

#include "imengine/FastTransform.h"
template class local::ImageEngine<local::FastTransform>;
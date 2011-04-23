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
    // do base class initialization
    AbsImageEngine::initialize(pixelsPerSide,pixelScale);
    // create a cache for generated images
    _generateCache.reset(new InterpolationData(pixelsPerSide,0,pixelScale,0,0));
    // create an interpolation data grid
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
    // Calculate the discrete Fourier transform of the source and PSF (with any offset
    // only applied to the source).
    bool srcChanged(_source->hasChanged()), psfChanged(_psf->hasChanged());
    if(srcChanged) _source->computeTransform(_sourceTransform);
    if(psfChanged) _psf->computeTransform(_psfTransform);
    // Map the requested (dx,dy) to our image grid.
    dx -= _imageGrid->getGridX();
    dy -= _imageGrid->getGridY();
    // Has anything changed?
    bool anyChange(srcChanged || psfChanged ||
        !_validLast || (dx != _lastDx) || (dy != _lastDy));
    if(anyChange) {
        // combine the source and PSF in Fourier space
        _imageTransform->setToProduct(_sourceTransform,_psfTransform,dx,dy);
        // build a grid of real-space convoluted image data
        _imageTransform->inverseTransform();        
    }
    // initialize our writer
    int N(getPixelsPerSide());
    double value,sum(0);
    writer.open(N,getPixelScale());
    // estimate the signal in each pixel
    for(int y = 0; y < N; ++y) {
        for(int x = 0; x < N; ++x) {
            // use cached values if possible
            if(anyChange) {
                value = estimatePixelValue(x,y);
                _generateCache->setValue(x,y,value);
            }
            else {
                value = _generateCache->getValue(x,y);
            }
            sum += writer.write(x,y,value);
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
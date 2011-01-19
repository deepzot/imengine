// Created 16-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_BILINEAR_IMAGE_ENGINE
#define IMENGINE_BILINEAR_IMAGE_ENGINE

#include "imengine/ImageEngine.h"

namespace imengine {
    // Implements an image engine that estimates the pixel data by integrating a bilinear
    // interpolating function across the pixel that is derived from the image function value
    // at the pixel corners.
	template <class T> class BilinearImageEngine : public ImageEngine<T> {
	public:
		BilinearImageEngine(AbsPixelFunction &source, AbsPixelFunction &psf,
		    int pixelsPerSide, double pixelScale = 1);
		virtual ~BilinearImageEngine();
    protected:
        virtual InterpolationData *createGrid();
        virtual double estimatePixelValue(int i, int j);
	private:
        double _norm;
        using ImageEngine<T>::_imageGrid; // makes this-> unecessary in implementation code
	}; // BilinearImageEngine
} // imengine

#endif // IMENGINE_BILINEAR_IMAGE_ENGINE

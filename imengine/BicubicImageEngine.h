// Created 16-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_BICUBIC_IMAGE_ENGINE
#define IMENGINE_BICUBIC_IMAGE_ENGINE

#include "imengine/ImageEngine.h"

namespace imengine {
    // Implements an image engine that estimates the pixel data by integrating a bicubic
    // interpolating function across the pixel that is derived from the image function value
    // at the pixel corners.
	template <class T> class BicubicImageEngine : public ImageEngine<T> {
	public:
		BicubicImageEngine(boost::shared_ptr<AbsPixelFunction> source,
		    boost::shared_ptr<AbsPixelFunction> psf);
		virtual ~BicubicImageEngine();
    protected:
        virtual InterpolationData *createGrid();
        virtual double estimatePixelValue(int i, int j);
	private:
        double _norm1,_norm13,_norm169;
        using ImageEngine<T>::_imageGrid; // makes this-> unecessary in implementation code
	}; // BicubicImageEngine
} // imengine

#endif // IMENGINE_BICUBIC_IMAGE_ENGINE

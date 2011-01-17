// Created 16-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_BICUBIC_IMAGE_ENGINE
#define IMENGINE_BICUBIC_IMAGE_ENGINE

#include "imengine/ImageEngine.h"

namespace imengine {
    // Implements an image engine that estimates the pixel data by integrating a bicubic
    // interpolating function across the pixel that is derived from the image function value
    // at the pixel corners.
	class BicubicImageEngine : public ImageEngine {
	public:
		BicubicImageEngine(AbsPixelFunction &source, AbsPixelFunction &psf,
		    int pixelsPerSide, double pixelScale = 1);
		virtual ~BicubicImageEngine();
    protected:
        virtual InterpolationData *createGrid();
        virtual double estimatePixelValue(int i, int j);
	private:
        double _norm1,_norm13,_norm169;
	}; // BicubicImageEngine
} // imengine

#endif // IMENGINE_BICUBIC_IMAGE_ENGINE

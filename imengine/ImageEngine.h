// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_IMAGE_ENGINE
#define IMENGINE_IMAGE_ENGINE

#include "imengine/AbsImageEngine.h"

namespace imengine {
    class AbsPixelFunction;
    class InterpolationData;
    class ImageWriter;
    // Generates pixelized images of a source convoluted with a psf.
	template <class T> class ImageEngine : public AbsImageEngine {
	public:
	    // Creates a new engine for the specified source and psf functions to generate
	    // square images of pixelsPerSide x pixelsPerSide pixels of dimension pixelScale.
		ImageEngine(AbsPixelFunction &source, AbsPixelFunction &psf,
		    int pixelsPerSide, double pixelScale = 1);
		virtual ~ImageEngine();
        // Initializes 
		// Generates an image with the source function offset by (dx,dy)
        virtual void generate(ImageWriter &writer, double dx = 0, double dy = 0);
    protected:
	private:
        T *_sourceTransform, *_psfTransform, *_imageTransform;
	}; // ImageEngine
} // imengine

#endif // IMENGINE_IMAGE_ENGINE

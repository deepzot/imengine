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
		ImageEngine(AbsPixelFunction &source, AbsPixelFunction &psf);
		virtual ~ImageEngine();
        // (Re)initializes the engine for the specified pixel grid size and scale
        virtual void initialize(int pixelsPerSide, double pixelScale = 1);
		// Generates an image with the source function offset by (dx,dy) and returns
		// the pixel sum
        virtual double generate(AbsImageWriter &writer, double dx = 0, double dy = 0);
    protected:
	private:
        T *_sourceTransform, *_psfTransform, *_imageTransform;
	}; // ImageEngine
} // imengine

#endif // IMENGINE_IMAGE_ENGINE

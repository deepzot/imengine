// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_IMAGE_ENGINE
#define IMENGINE_IMAGE_ENGINE

namespace imengine {
    class AbsPixelFunction;
    class ImageData;
    class TransformData;
    // Generates pixelized images of a source convoluted with a psf.
	class ImageEngine {
	public:
	    // Creates a new engine for the specified source and psf functions to generate
	    // square images of pixelsPerSide x pixelsPerSide pixels.
		ImageEngine(const AbsPixelFunction &source, const AbsPixelFunction &psf, int pixelsPerSide);
		virtual ~ImageEngine();
		// Generates an image at the specified pixel scale, with the source function offset by (dx,dy)
        ImageData *generate(double pixelScale = 1, double dx = 0, double dy = 0);
	private:
        const AbsPixelFunction &_source, &_psf;
        int _pixelsPerSide;
        TransformData *_sourceTransform, *_psfTransform, *_imageTransform;
	}; // ImageEngine
} // imengine

#endif // IMENGINE_IMAGE_ENGINE

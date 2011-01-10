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
	    // square images of pixelsPerSide x pixelsPerSide pixels with each pixel measuring
	    // pixelScale on a side.
		ImageEngine(AbsPixelFunction &source, AbsPixelFunction &psf,
		    int pixelsPerSide, double pixelScale = 1);
		virtual ~ImageEngine();
		// Read-only accessors
        inline int getPixelsPerSide() const { return _pixelsPerSide; }
        inline double getPixelScale() const { return _pixelScale; }
		// Generates an image with the source function offset by (dx,dy)
        ImageData *generate(double dx = 0, double dy = 0);
    protected:
        int gridSize;
        double gridSpacing,gridX,gridY;
        virtual void setGridParams();
	private:
        AbsPixelFunction &_source, &_psf;
        int _pixelsPerSide;
        double _pixelScale;
        TransformData *_sourceTransform, *_psfTransform, *_imageTransform;
	}; // ImageEngine
} // imengine

#endif // IMENGINE_IMAGE_ENGINE

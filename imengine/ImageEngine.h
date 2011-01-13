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
	    // square images of pixelsPerSide x pixelsPerSide pixels of dimension pixelScale.
		ImageEngine(AbsPixelFunction &source, AbsPixelFunction &psf,
		    int pixelsPerSide, double pixelScale = 1);
		virtual ~ImageEngine();
		// Read-only accessors
        inline int getPixelsPerSide() const { return _pixelsPerSide; }
        inline double getPixelScale() const { return _pixelScale; }
        // Initializes 
		// Generates an image with the source function offset by (dx,dy)
        ImageData *generate(double dx = 0, double dy = 0);
    protected:
        // Returns a pointer to a newly created TransformData with parameters appropriate
        // for the requested pixel size and pixelation method
        virtual TransformData *createImageTransform() = 0;
        // Estimates the signal in pixel (i,j) using the tabulated values in _imageData
        virtual double estimatePixelValue(int i, int j) = 0;
        double *_imageData;
	private:
        AbsPixelFunction &_source, &_psf;
        int _pixelsPerSide;
        double _pixelScale;
        TransformData *_sourceTransform, *_psfTransform, *_imageTransform;
	}; // ImageEngine
} // imengine

#endif // IMENGINE_IMAGE_ENGINE

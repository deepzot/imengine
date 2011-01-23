// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ABS_IMAGE_ENGINE
#define IMENGINE_ABS_IMAGE_ENGINE

#include "boost/utility.hpp"

namespace imengine {
    class AbsPixelFunction;
    class InterpolationData;
    class AbsImageWriter;
    // Generates pixelized images of a source convoluted with a psf.
	class AbsImageEngine : boost::noncopyable {
	public:
	    // Creates a new engine for the specified source and psf functions to generate
	    // square images of pixelsPerSide x pixelsPerSide pixels of dimension pixelScale.
		AbsImageEngine(AbsPixelFunction &source, AbsPixelFunction &psf,
		    int pixelsPerSide, double pixelScale = 1);
		virtual ~AbsImageEngine();
		// Read-only accessors
        int getPixelsPerSide() const;
        double getPixelScale() const;
        // Initializes 
		// Generates an image with the source function offset by (dx,dy)
        virtual void generate(AbsImageWriter &writer, double dx = 0, double dy = 0) = 0;
    protected:
        // Returns a pointer to a newly created InterpolationData with parameters appropriate
        // for the requested pixel size and pixelation method
        virtual InterpolationData *createGrid() = 0;
        // Estimates the signal in pixel (i,j) using the tabulated values in _imageData
        virtual double estimatePixelValue(int i, int j) = 0;
        InterpolationData *_imageGrid, *_workspace;
        int _pixelsPerSide;
        double _pixelScale;
        double _scaleSquared;
        AbsPixelFunction &_source, &_psf;
	private:
	}; // AbsImageEngine
	
    inline int AbsImageEngine::getPixelsPerSide() const { return _pixelsPerSide; }    
    inline double AbsImageEngine::getPixelScale() const { return _pixelScale; }
    
} // imengine

#endif // IMENGINE_ABS_IMAGE_ENGINE

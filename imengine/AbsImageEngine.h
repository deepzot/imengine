// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ABS_IMAGE_ENGINE
#define IMENGINE_ABS_IMAGE_ENGINE

#include "boost/utility.hpp"
#include "boost/smart_ptr.hpp"

namespace imengine {
    class AbsPixelFunction;
    class InterpolationData;
    class AbsImageWriter;
    // Generates pixelized images of a source convoluted with a psf.
	class AbsImageEngine : boost::noncopyable {
	public:
	    // Creates a new engine for the specified source and psf functions.
		AbsImageEngine(AbsPixelFunction &source, AbsPixelFunction &psf);
		virtual ~AbsImageEngine();
		// Read-only accessors
        int getPixelsPerSide() const;
        double getPixelScale() const;
        bool isInitialized() const;
        // (Re)initializes the engine for the specified pixel grid size and scale
        virtual void initialize(int pixelsPerSide, double pixelScale = 1) = 0;
		// Generates an image with the source function offset by (dx,dy) and returns
		// the pixel sum
        virtual double generate(AbsImageWriter &writer, double dx = 0, double dy = 0) = 0;
    protected:
        // Returns a pointer to a newly created InterpolationData with parameters appropriate
        // for the requested pixel size and pixelation method
        virtual InterpolationData *createGrid() = 0;
        // Estimates the signal in pixel (i,j) using the tabulated values in _imageData
        virtual double estimatePixelValue(int i, int j) = 0;
        
        double _scaleSquared;
        AbsPixelFunction &_source, &_psf;
        boost::shared_ptr<InterpolationData> _imageGrid,_workspace;

	private:
        void _reset();
        int _pixelsPerSide;
        double _pixelScale;
        bool _initialized;
	}; // AbsImageEngine
	
    inline int AbsImageEngine::getPixelsPerSide() const { return _pixelsPerSide; }    
    inline double AbsImageEngine::getPixelScale() const { return _pixelScale; }
    inline bool AbsImageEngine::isInitialized() const { return _initialized; }
        
} // imengine

#endif // IMENGINE_ABS_IMAGE_ENGINE

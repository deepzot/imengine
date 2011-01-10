// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MIDPOINT_IMAGE_ENGINE
#define IMENGINE_MIDPOINT_IMAGE_ENGINE

#include "imengine/ImageEngine.h"

namespace imengine {
    // Implements an image engine that estimates the pixel data by evaluating the image
    // function at the midpoint of each pixel. This is a fast but low accuracy method.
	class MidpointImageEngine : public ImageEngine {
	public:
		MidpointImageEngine(AbsPixelFunction &source, AbsPixelFunction &psf,
		    int pixelsPerSide, double pixelScale = 1);
		virtual ~MidpointImageEngine();
    protected:
        virtual void setGridParams();
	private:
	}; // MidpointImageEngine
} // imengine

#endif // IMENGINE_MIDPOINT_IMAGE_ENGINE

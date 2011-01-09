// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MIDPOINT_IMAGE_ENGINE
#define IMENGINE_MIDPOINT_IMAGE_ENGINE

#include "imengine/ImageEngine.h"

namespace imengine {
	class MidpointImageEngine : public ImageEngine {
	public:
		MidpointImageEngine(const AbsPixelFunction &source, const AbsPixelFunction &psf,
		    int pixelsPerSide, double pixelScale = 1);
		virtual ~MidpointImageEngine();
    protected:
        virtual void setGridParams();
	private:
	}; // MidpointImageEngine
} // imengine

#endif // IMENGINE_MIDPOINT_IMAGE_ENGINE

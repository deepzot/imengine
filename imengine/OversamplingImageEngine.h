// Created 25-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_OVERSAMPLING_IMAGE_ENGINE
#define IMENGINE_OVERSAMPLING_IMAGE_ENGINE

#include "imengine/AbsImageEngine.h"
#include "imengine/ptr_types.h"

namespace imengine {
	class OversamplingImageEngine : public AbsImageEngine {
	public:
	    // Create an engine that oversamples the specified engine by subdividing each
	    // pixel into the specified number of subpixels along each axis.
		OversamplingImageEngine(AbsImageEnginePtr engine, int subpixels);
		virtual ~OversamplingImageEngine();
        // (Re)initializes the engine for the specified pixel grid size and scale
        virtual void initialize(int pixelsPerSide, double pixelScale = 1);
		// Generates an image with the source function offset by (dx,dy) and returns
		// the pixel sum
        virtual double generate(AbsImageWriter &writer, double dx = 0, double dy = 0);
	private:
        AbsImageEnginePtr _engine;
        int _subpixels;
	}; // OversamplingImageEngine
} // imengine

#endif // IMENGINE_OVERSAMPLING_IMAGE_ENGINE

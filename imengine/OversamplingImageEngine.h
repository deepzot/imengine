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
	private:
	}; // OversamplingImageEngine
} // imengine

#endif // IMENGINE_OVERSAMPLING_IMAGE_ENGINE

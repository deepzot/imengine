// Created 19-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_RESIZING_IMAGE_ENGINE
#define IMENGINE_RESIZING_IMAGE_ENGINE

#include "imengine/AbsImageEngine.h"
#include "imengine/ptr_types.h"

namespace imengine {
    class ArrayImageWriter;
	class ResizingImageEngine : public AbsImageEngine {
	public:
	    // Creates an engine that generates the image using a different pixel
	    // size than requested, where the difference is specified by a pixel
	    // margin size:
	    //
	    //   generatedPixelsPerSide = requestedPixelsPerSide + 2*pixelMargin
	    //
	    // Note that the pixel margin can be positive or negative. Positive values
	    // are useful to reduce aliasing effects when the generated image has some
	    // leakage outside the requested image size (that would otherwise be aliased
	    // into the final image because of the assumed Fourier periodicity). Negative
	    // values are useful to speed up generation when the image is centrally
	    // concentrated and an outer pixel border can safely be forced to zero.
		ResizingImageEngine(AbsImageEnginePtr engine, int pixelMargin);
		virtual ~ResizingImageEngine();
        // (Re)initializes the engine for the specified pixel grid size and scale.
        // Throws an exception if the requested pixelsPerSide is too small for
        // this engine's pixelMargin (i.e., pixelsPerSide + 2*pixelMargin <= 0).
        virtual void initialize(int pixelsPerSide, double pixelScale = 1);
		// Generates an image with the source function offset by (dx,dy) and returns
		// the pixel sum
        virtual double generate(AbsImageWriter &writer, double dx = 0, double dy = 0);
	private:
        boost::scoped_ptr<ArrayImageWriter> _generatedPixelData;
        AbsImageEnginePtr _engine;
        int _pixelMargin;
	}; // ResizingImageEngine
} // imengine

#endif // IMENGINE_RESIZING_IMAGE_ENGINE

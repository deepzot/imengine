// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MIDPOINT_IMAGE_ENGINE
#define IMENGINE_MIDPOINT_IMAGE_ENGINE

#include "imengine/ImageEngine.h"

namespace imengine {
    // Implements an image engine that estimates the pixel data by evaluating the image
    // function at the midpoint of each pixel. This is a fast but low accuracy method.
	template <class T> class MidpointImageEngine : public ImageEngine<T> {
	public:
		MidpointImageEngine(AbsPixelFunction &source, AbsPixelFunction &psf);
		virtual ~MidpointImageEngine();
    protected:
        virtual InterpolationData *createGrid();
        virtual double estimatePixelValue(int i, int j);
	private:
        double _norm;
	}; // MidpointImageEngine
} // imengine

#endif // IMENGINE_MIDPOINT_IMAGE_ENGINE

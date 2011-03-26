// Created 26-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ABS_IMAGE_FILTER
#define IMENGINE_ABS_IMAGE_FILTER

#include "imengine/AbsImageWriter.h"
#include "imengine/ptr_types.h"

namespace imengine {
	class AbsImageFilter : public AbsImageWriter {
	public:
		AbsImageFilter(AbsImageWriterPtr writer);
		virtual ~AbsImageFilter();
		// Starts writing a new image with the specified pixel size and scale
        virtual void open(int size, double scale);
        // Writes a single pixel value. Will be called in row-wise order for each pixel in turn.
        virtual void write(int x, int y, double value);
        // Ends writing the current image
        virtual void close();
        // Filters each pixel before writing it.
        virtual double filter(int x, int y, double value) const = 0;
	private:
        AbsImageWriterPtr _writer;
	}; // AbsImageFilter
} // imengine

#endif // IMENGINE_ABS_IMAGE_FILTER

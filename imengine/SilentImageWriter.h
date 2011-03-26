// Created 23-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_SILENT_IMAGE_WRITER
#define IMENGINE_SILENT_IMAGE_WRITER

#include "imengine/AbsImageWriter.h"

namespace imengine {
	class SilentImageWriter : public AbsImageWriter {
	public:
		SilentImageWriter();
		virtual ~SilentImageWriter();
		// Starts writing a new image with the specified pixel size and scale
        virtual void open(int size, double scale);
        // Writes a single pixel value. Will be called in row-wise order for each pixel in turn.
        virtual double write(int x, int y, double value);
        // Ends writing the current image
        virtual void close();
	private:
	}; // SilentImageWriter
} // imengine

#endif // IMENGINE_SILENT_IMAGE_WRITER

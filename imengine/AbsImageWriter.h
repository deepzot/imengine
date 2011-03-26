// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ABS_IMAGE_WRITER
#define IMENGINE_ABS_IMAGE_WRITER

namespace imengine {
	class AbsImageWriter {
	public:
	    // Declares an abstract interface for writing images
		AbsImageWriter();
		virtual ~AbsImageWriter();
		// Starts writing a new image with the specified pixel size and scale
        virtual void open(int size, double scale) = 0;
        // Writes a single pixel value. Will be called in row-wise order for each pixel in turn.
        // Returns the actual value written.
        virtual double write(int x, int y, double value) = 0;
        // Ends writing the current image
        virtual void close() = 0;
	private:
	}; // AbsImageWriter
} // imengine

#endif // IMENGINE_ABS_IMAGE_WRITER

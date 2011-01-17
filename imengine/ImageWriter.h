// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_IMAGE_WRITER
#define IMENGINE_IMAGE_WRITER

namespace imengine {
	class ImageWriter {
	public:
		ImageWriter();
		virtual ~ImageWriter();
		// Starts writing a new image
        virtual void open();
        // Writes a single pixel value. Will be called in row-wise order for each pixel in turn.
        virtual void write(int x, int y, double value);
        // Ends writing the current image
        virtual void close();
	private:
	}; // ImageWriter
} // imengine

#endif // IMENGINE_IMAGE_WRITER

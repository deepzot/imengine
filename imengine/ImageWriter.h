// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_IMAGE_WRITER
#define IMENGINE_IMAGE_WRITER

namespace imengine {
	class ImageWriter {
	public:
		ImageWriter();
		virtual ~ImageWriter();
        virtual void open();
        virtual void write(int x, int y, double value);
        virtual void close();
	private:
	}; // ImageWriter
} // imengine

#endif // IMENGINE_IMAGE_WRITER

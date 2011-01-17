// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_IMAGE_FILE_WRITER
#define IMENGINE_IMAGE_FILE_WRITER

#include "imengine/ImageWriter.h"

#include <string>

namespace imengine {
    // Writes pixel values to the named file (or else stdout) with one line per row
	class ImageFileWriter : public ImageWriter {
	public:
		ImageFileWriter(const char *filename = "");
		virtual ~ImageFileWriter();
        void open();
        void write(int x, int y, double value);
        void close();
	private:
        std::string _filename;
        std::ostream *_os;
        int _lastY;
	}; // ImageFileWriter
} // imengine

#endif // IMENGINE_IMAGE_FILE_WRITER

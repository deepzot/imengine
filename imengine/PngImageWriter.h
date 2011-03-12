// Created 02-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_PNG_IMAGE_WRITER
#define IMENGINE_PNG_IMAGE_WRITER

#include "imengine/ArrayImageWriter.h"

#include "boost/function.hpp"

#include <string>

namespace imengine {
	class PngImageWriter : public ArrayImageWriter {
	public:
		PngImageWriter(std::string const &filename);
		virtual ~PngImageWriter();
        virtual void open(int size, double scale);
        virtual void close();
	private:
        std::string _filename;
	}; // PngImageWriter
	
	// Writes a square (size x size pixels) PNG image to the specified file or stdout.
	// The format is 16-bit grayscale, with the input data mapped so that its maximum
	// value corresponds to full white, and any values <= 0 are mapped to black.
    typedef boost::function<float (int,int)> ImageDataAccessor;
    void writePngImage(std::string const &filename, int size, ImageDataAccessor accessor);
    
} // imengine

#endif // IMENGINE_PNG_IMAGE_WRITER

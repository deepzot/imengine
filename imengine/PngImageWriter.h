// Created 02-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_PNG_IMAGE_WRITER
#define IMENGINE_PNG_IMAGE_WRITER

#include "imengine/ArrayImageWriter.h"

#include "boost/function.hpp"

#include <cfloat>
#include <string>

namespace imengine {
	class PngImageWriter : public ArrayImageWriter {
	public:
	    // Creates a new image writer that outputs 16-bit gray scale images.
	    // See comments for writePngImage for details on mapMin, mapMax. By default,
	    // the black point is mapped to zero and the white point is autoscaled to 
	    // the actual pixel data maximum.
		PngImageWriter(std::string const &filename, float mapMin = 0, float mapMax = +FLT_MAX);
		virtual ~PngImageWriter();
        virtual void open(int size, double scale);
        virtual void close();
	private:
        std::string _filename;
        float _mapMin, _mapMax;
	}; // PngImageWriter
	
	// Writes a square (size x size pixels) PNG image to the specified file or stdout.
	// The format is 16-bit grayscale and the mapping from floating point value to
	// grayscale is controlled by the mapMin and mapMax arguments: the default values
	// will autoscale the black/white point to the actual min/max data value. Specifying
	// a different value will result in a fixed black/white point.
    typedef boost::function<float (int,int)> ImageDataAccessor;
    void writePngImage(std::string const &filename, ImageDataAccessor accessor,
        int size, float mapMin = -FLT_MAX, float mapMax = +FLT_MAX);
    
} // imengine

#endif // IMENGINE_PNG_IMAGE_WRITER

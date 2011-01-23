// Created 23-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_ARRAY_IMAGE_WRITER
#define IMENGINE_ARRAY_IMAGE_WRITER

#include "imengine/AbsImageWriter.h"

namespace imengine {
	class ArrayImageWriter : public AbsImageWriter {
	public:
		ArrayImageWriter();
		virtual ~ArrayImageWriter();
		// Starts writing a new image with the specified pixel size and scale
        virtual void open(int size, double scale);
        // Writes a single pixel value. Will be called in row-wise order for each pixel in turn.
        virtual void write(int x, int y, double value);
        // Ends writing the current image
        virtual void close();
        // Returns the size of the last image written, or zero
        int getSize() const;
        // Returns the value at coordinates (x,y) of the last image written, or zero
        double getValue(int x, int y) const;
	private:
        int _size;
        double *_data;
	}; // ArrayImageWriter
	
	// Compares two images saved to arrays and returns true if they match within
	// the specified absolute |v1-v2| and relative |v1-v2|/|v1+v2| tolerances.
	// Prints info about the comparison to std::cout if verbose is true.
    bool compareImages(ArrayImageWriter const &first, ArrayImageWriter const &second,
        bool verbose = false, double abstol = 1e-14, double reltol = 1e-10);
	
    inline int ArrayImageWriter::getSize() const { return _size; }
    
    inline double ArrayImageWriter::getValue(int x, int y) const {
        return (0 != _data) ? _data[x + y*_size] : 0;
    }

} // imengine

#endif // IMENGINE_ARRAY_IMAGE_WRITER

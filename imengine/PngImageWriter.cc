// Created 02-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/PngImageWriter.h"
#include "imengine/RuntimeError.h"

#include "config.h" // propagates HAVE_LIBPNG from configure
#ifdef HAVE_LIBPNG
#include "png.h"
#endif

#include "boost/bind.hpp"

#include <cassert>
#include <cstdio>

namespace local = imengine;

local::PngImageWriter::PngImageWriter(std::string const &filename, bool inverted,
float mapMin, float mapMax)
: ArrayImageWriter(), _filename(filename), _inverted(inverted),
_mapMin(mapMin), _mapMax(mapMax)
{
#ifndef HAVE_LIBPNG
    throw RuntimeError("PngImageWriter: library not built with optional png support.");
#endif
}

local::PngImageWriter::~PngImageWriter() {
}

void local::PngImageWriter::open(int size, double scale) {
    ArrayImageWriter::open(size,scale);
}

void local::PngImageWriter::close() {
    writePngImage(_filename, boost::bind(&local::PngImageWriter::getValue,this,_1,_2),
        getSize(), _inverted, _mapMin, _mapMax);
    ArrayImageWriter::close();
}

void local::writePngImage(std::string const &filename, ImageDataAccessor getValue,
    int size, bool inverted, float mapMin, float mapMax) {
#ifdef HAVE_LIBPNG
    // open the specified file or stdout
    std::FILE *_file;
    if(0 == filename.length()) {
        _file = stdout;
    }
    else {
        _file = std::fopen(filename.c_str(),"wb");
    }

    // scan through the image data to find its min/max limits, if necessary
    float max(getValue(0,0)),min(max);
    if(mapMin == -FLT_MAX || mapMax == +FLT_MAX) {
        for(int j = 0; j < size; j++) {
            for(int i = 0; i < size; i++) {
                float value(getValue(i,j));
                if(value > max) max = value;
                if(value < min) min = value;
            }
        }
        if(mapMin == -FLT_MAX) mapMin = min;
        if(mapMax == +FLT_MAX) mapMax = max;
    }

    // calculate the float to int mapping
    double range(mapMax-mapMin);
    assert(range > 0);
    double scale(PngImageWriter::MaxPixel/range);

    // create a png_struct
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)0, 0, 0);
    if(!png_ptr) {
        printf("PngImageWriter: png_create_write_struct failed.\n");
        return;
    }
    // create a png info_ptr
    png_infop info_ptr = png_create_info_struct(png_ptr); 
    if (!info_ptr) { 
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        printf("PngImageWriter: png_create_info_struct failed.\n");
        return;
    }
    // initialize output to our open file
    png_init_io(png_ptr, _file);
    // specify the png header fields for 16-bit grayscale non-interlaced
    png_set_IHDR(png_ptr, info_ptr, size, size, 16, PNG_COLOR_TYPE_GRAY,
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    // write the header now
    png_write_info(png_ptr, info_ptr);
    // allocate and fill the memory for our output image data
    png_bytep *row_pointers = (png_bytep*)png_malloc(png_ptr, size*png_sizeof(png_bytep)); 
    for(int j = 0; j < size; j++) {
        // re-map rows so that the first row is at the bottom of the image
        int j2(size-1-j);
        row_pointers[j2] = (png_byte*)png_malloc(png_ptr, 2*size*png_sizeof(png_byte));
        png_bytep row(row_pointers[j2]);
        int ivalue;
        for (int i = 0; i < size; i++) {
            // scale pixel value to 16-bit range            
            float value(getValue(i,j) - mapMin);
            if(value < 0) value = 0;
            if(value > range) value = range;
            ivalue = static_cast<int>(value*scale+0.5);
            assert(ivalue >= 0 && ivalue <= PngImageWriter::MaxPixel);
            // invert the image (black <-> white) if requested
            if(inverted) {
                ivalue = PngImageWriter::MaxPixel - ivalue;
            }
            // store 16-bit value in big-endian order
            *row++ = (png_byte)((ivalue & 0xff00) >> 8);
            *row++ = (png_byte)(ivalue & 0xff);
        }
    }
    // write the image data now
    png_write_image(png_ptr, row_pointers);
    // close out the file
    png_write_end(png_ptr, info_ptr);
    // png cleanup
    for(int i = 0; i < size; i++) {
        png_free(png_ptr, row_pointers[i]);
    }
    png_free(png_ptr, row_pointers);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    // close our file now
    if(_file != stdout) {
        std::fclose(_file);
    }
    _file = 0;
#endif
}

// Created 02-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/PngImageWriter.h"

#include "png/include/png.h"

#include <cassert>

namespace local = imengine;

local::PngImageWriter::PngImageWriter(std::string const &filename)
: ArrayImageWriter(), _filename(filename), _file(0)
{
}

local::PngImageWriter::~PngImageWriter() {
    // this should never happen if open/close calls are balanced
    assert(0 == _file);
}

void local::PngImageWriter::open(int size, double scale) {
    ArrayImageWriter::open(size,scale);
    // this should never happen if open/close calls are balanced
    assert(0 == _file);
    // (re)open our named file
    _file = std::fopen(_filename.c_str(),"wb");
}

void local::PngImageWriter::close() {
    // this should never happen if open/close calls are balanced
    assert(0 != _file);
    // scan through the image data to find its min/max limits
    double max(getValue(0,0));
    int N(getSize());
    for(int j = 0; j < N; j++) {
        for(int i = 0; i < N; i++) {
            double value(getValue(i,j));
            if(value > max) max = value;
        }
    }
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
    png_set_IHDR(png_ptr, info_ptr, N, N, 16, PNG_COLOR_TYPE_GRAY,
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    // write the header now
    png_write_info(png_ptr, info_ptr);
    // allocate and fill the memory for our output image data
    double scale(((1<<16)-1)/max);
    png_bytep *row_pointers = (png_bytep*)png_malloc(png_ptr, N*png_sizeof(png_bytep)); 
    for(int j = 0; j < N; j++) {
        // re-map rows so that the first row is at the bottom of the image
        int j2(N-1-j);
        row_pointers[j2] = (png_byte*)png_malloc(png_ptr, 2*N*png_sizeof(png_byte));
        png_bytep row(row_pointers[j2]);
        for (int i = 0; i < N; i++) {
            // scale pixel value to 16-bit range
            double value(getValue(i,j));
            int ivalue = (int)(value*scale+0.5);
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
    for(int i = 0; i < N; i++) {
        png_free(png_ptr, row_pointers[i]);
    }
    png_free(png_ptr, row_pointers);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    // close our file now
    std::fclose(_file);
    _file = 0;
    ArrayImageWriter::close();
}
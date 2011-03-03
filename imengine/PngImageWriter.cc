// Created 02-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/PngImageWriter.h"

#include "png/include/png.h"

#include <cassert>

namespace local = imengine;

local::PngImageWriter::PngImageWriter(std::string const &filename)
: AbsImageWriter(), _filename(filename), _file(0)
{
}

local::PngImageWriter::~PngImageWriter() {
    // this should never happen if open/close calls are balanced
    assert(0 == _file);
}

void local::PngImageWriter::open(int size, double scale) {
    // this should never happen if open/close calls are balanced
    assert(0 == _file);
    // (re)open our named file
    _file = std::fopen(_filename.c_str(),"wb");
    _lastX = size-1;
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
}

void local::PngImageWriter::write(int x, int y, double value) {
    // this should never happen if open/close calls are balanced
    assert(0 != _file);
    //*_os << ' ' << value;
    if(x == _lastX) {
        //*_os << std::endl;
    }
}

void local::PngImageWriter::close() {
    // this should never happen if open/close calls are balanced
    assert(0 != _file);
    std::fclose(_file);
    _file = 0;
}
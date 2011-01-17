// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ImageFileWriter.h"

#include <iostream>
#include <fstream>

namespace local = imengine;

local::ImageFileWriter::ImageFileWriter(const char *filename)
: _filename(filename), _os(0)
{ }

local::ImageFileWriter::~ImageFileWriter() { }

void local::ImageFileWriter::open() {
    if(_filename != "") {
        _os = new std::fstream(_filename.c_str(), std::fstream::out | std::fstream::trunc);
    }
    else {
        _os = &std::cout;
    }
    _lastY = 0;
}

void local::ImageFileWriter::write(int x, int y, double value) {
    if(y > _lastY) {
        *_os << std::endl;
        _lastY = y;
    }
    *_os << ' ' << value;
}

void local::ImageFileWriter::close() {
    *_os << std::endl;
    if(_filename != "") {
        delete _os;
        _os = 0;
    }
}
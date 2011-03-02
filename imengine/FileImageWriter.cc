// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/FileImageWriter.h"

#include <iostream>
#include <fstream>
#include <cassert>

namespace local = imengine;

local::FileImageWriter::FileImageWriter(std::string const &filename)
: AbsImageWriter(), _filename(filename), _os(0)
{ }

local::FileImageWriter::~FileImageWriter() {
    // this should never happen if open/close calls are balanced
    assert(0 == _os);
}

void local::FileImageWriter::open(int size, double scale) {
    // this should never happen if open/close calls are balanced
    assert(0 == _os);
    // (re)open our named file if a name has been specified
    if(_filename != "") {
        _os = new std::fstream(_filename.c_str(), std::fstream::out | std::fstream::trunc);
    }
    else {
        _os = &std::cout;
    }
    _lastX = size-1;
}

void local::FileImageWriter::write(int x, int y, double value) {
    *_os << ' ' << value;
    if(x == _lastX) {
        *_os << std::endl;
    }
}

void local::FileImageWriter::close() {
    if(_filename != "") {
        delete _os;
    }
    _os = 0;
}
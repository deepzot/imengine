// Created 26-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/AbsImageFilter.h"

namespace local = imengine;

local::AbsImageFilter::AbsImageFilter(AbsImageWriterPtr writer)
: _writer(writer)
{ }

local::AbsImageFilter::~AbsImageFilter() { }

void local::AbsImageFilter::open(int size, double scale) {
    _writer->open(size,scale);
}

void local::AbsImageFilter::write(int x, int y, double value) {
    _writer->write(x, y, filter(x, y, value));
}

void local::AbsImageFilter::close() {
    _writer->close();
}

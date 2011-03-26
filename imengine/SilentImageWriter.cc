// Created 23-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/SilentImageWriter.h"

namespace local = imengine;

local::SilentImageWriter::SilentImageWriter()
: AbsImageWriter()
{ }

local::SilentImageWriter::~SilentImageWriter() { }

void local::SilentImageWriter::open(int size, double scale) { }

double local::SilentImageWriter::write(int x, int y, double value) { return value; }

void local::SilentImageWriter::close() { }

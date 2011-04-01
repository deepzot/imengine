// Created 1-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/InvalidValue.h"

namespace local = imengine;

local::InvalidValue::InvalidValue(std::string const& reason) : RuntimeError(reason)
{
}

local::InvalidValue::~InvalidValue() throw () { }

void local::assertRange(int value, int min, int max) {
}

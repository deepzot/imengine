// Created 1-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/RuntimeError.h"

namespace local = imengine;
	
local::RuntimeError::RuntimeError(const std::string& reason)
: std::runtime_error(reason)
{
}

local::RuntimeError::~RuntimeError() throw () { }

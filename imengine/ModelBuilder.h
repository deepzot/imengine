// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODEL_BUILDER
#define IMENGINE_MODEL_BUILDER

#include "imengine/ptr_types.h"

#include <string>

namespace imengine {
    class AbsPixelFunction;
	class ModelBuilder {
	public:
		ModelBuilder();
		virtual ~ModelBuilder();
        AbsPixelFunctionPtr parse(std::string const &input);
	}; // ModelBuilder
} // imengine

#endif // IMENGINE_MODEL_BUILDER

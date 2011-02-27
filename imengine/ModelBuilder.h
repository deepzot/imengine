// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODEL_BUILDER
#define IMENGINE_MODEL_BUILDER

#include <string>

namespace imengine {
    //class std::string;
	class ModelBuilder {
	public:
		ModelBuilder();
		virtual ~ModelBuilder();
        void parse(std::string const &input);
	private:
	}; // ModelBuilder
} // imengine

#endif // IMENGINE_MODEL_BUILDER

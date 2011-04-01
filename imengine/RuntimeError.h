// Created 1-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_RUNTIME_ERROR
#define IMENGINE_RUNTIME_ERROR

#include <stdexcept>

namespace imengine {
    // Represents a run-time error detected by code within this namespace
	class RuntimeError : public std::runtime_error {
	public:
		explicit RuntimeError(const std::string& reason);
		virtual ~RuntimeError() throw ();
	private:
	}; // RuntimeError
} // imengine

#endif // IMENGINE_RUNTIME_ERROR

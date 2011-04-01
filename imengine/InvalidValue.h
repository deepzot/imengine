// Created 1-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_INVALID_VALUE
#define IMENGINE_INVALID_VALUE

#include "imengine/RuntimeError.h"

namespace imengine {
  // Represents a runtime error due to an invalid numeric value
  class InvalidValue : public RuntimeError {
  public:
    InvalidValue(const std::string& reason);
    virtual ~InvalidValue() throw ();
  }; // InvalidValue

  // Checks that the specified value is within the specified range and returns
  // silently, or else throws an InvalidValue with a helpful message.
  void assertRange(int value, int min, int max);

} // imengine

#endif // IMENGINE_INVALID_VALUE

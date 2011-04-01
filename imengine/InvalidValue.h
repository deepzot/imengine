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

  // Checks that min <= value <= max and returns silently, or else throws
  // an InvalidValue with a helpful message.
  template <typename T>
    void assertRange(std::string const &what, T value, T min, T max);

  // Checks that min <= value and returns silently, or else throws an
  // InvalidValue with a helpful message.
  template <typename T>
    void assertMin(std::string const &what, T value, T min);

  // Checks that value <= max and returns silently, or else throws an
  // InvalidValue with a helpful message.
  template <typename T>
    void assertMax(std::string const &what, T value, T max);

} // imengine

#endif // IMENGINE_INVALID_VALUE

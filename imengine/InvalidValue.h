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

  // Checks that min <= value and returns silently, or else throws an
  // InvalidValue with a helpful message.
  template <typename T>
    void assertGreaterThanOrEqualTo(std::string const &what, T value, T min);

  // Checks that min < value and returns silently, or else throws an
  // InvalidValue with a helpful message.
  template <typename T>
    void assertGreaterThan(std::string const &what, T value, T min);

  // Checks that value <= max and returns silently, or else throws an
  // InvalidValue with a helpful message.
  template <typename T>
    void assertLessThanOrEqualTo(std::string const &what, T value, T max);

  // Checks that value < max and returns silently, or else throws an
  // InvalidValue with a helpful message.
  template <typename T>
    void assertLessThan(std::string const &what, T value, T max);

} // imengine

#endif // IMENGINE_INVALID_VALUE

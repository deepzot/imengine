// Created 1-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/InvalidValue.h"

#include "boost/lexical_cast.hpp"

#include <string>

namespace local = imengine;

local::InvalidValue::InvalidValue(std::string const& reason) : RuntimeError(reason)
{
}

local::InvalidValue::~InvalidValue() throw () { }

template <typename T>
void local::assertGreaterThanOrEqualTo(std::string const &what, T value, T min) {
  if(value < min) {
    std::string reason("Invalid Value: ");
    reason += what;
    reason += " = " + boost::lexical_cast<std::string>(value);
    reason += ", should be >= ";
    reason += boost::lexical_cast<std::string>(min);
    throw InvalidValue(reason);
  }
}

template <typename T>
void local::assertGreaterThan(std::string const &what, T value, T min) {
  if(value <= min) {
    std::string reason("Invalid Value: ");
    reason += what;
    reason += " = " + boost::lexical_cast<std::string>(value);
    reason += ", should be > ";
    reason += boost::lexical_cast<std::string>(min);
    throw InvalidValue(reason);
  }
}

template <typename T>
void local::assertLessThanOrEqualTo(std::string const &what, T value, T max) {
  if(value > max) {
    std::string reason("Invalid Value: ");
    reason += what;
    reason += " = " + boost::lexical_cast<std::string>(value);
    reason += ", should be <= ";
    reason += boost::lexical_cast<std::string>(max);
    throw InvalidValue(reason);
  }
}

template <typename T>
void local::assertLessThan(std::string const &what, T value, T max) {
  if(value >= max) {
    std::string reason("Invalid Value: ");
    reason += what;
    reason += " = " + boost::lexical_cast<std::string>(value);
    reason += ", should be < ";
    reason += boost::lexical_cast<std::string>(max);
    throw InvalidValue(reason);
  }
}

template <typename T>
void local::assertNotEqualTo(std::string const &what, T value, T illegal) {
  if(value == illegal) {
    std::string reason("Invalid Value: ");
    reason += what;
    reason += " = " + boost::lexical_cast<std::string>(value);
    reason += ", should be != ";
    reason += boost::lexical_cast<std::string>(illegal);
    throw InvalidValue(reason);
  }
}

// explicit template instantiations for int, double args

template void local::assertGreaterThan<int>(std::string const&,int,int);
template void local::assertGreaterThan<double>(std::string const&,double,double);

template void local::assertGreaterThanOrEqualTo<int>(std::string const&,int,int);
template void local::assertGreaterThanOrEqualTo<double>(std::string const&,double,double);

template void local::assertLessThan<int>(std::string const&,int,int);
template void local::assertLessThan<double>(std::string const&,double,double);

template void local::assertLessThanOrEqualTo<int>(std::string const&,int,int);
template void local::assertLessThanOrEqualTo<double>(std::string const&,double,double);

template void local::assertNotEqualTo<int>(std::string const&,int,int);
template void local::assertNotEqualTo<double>(std::string const&,double,double);

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
void local::assertRange(std::string const &what, T value, T min, T max) {
  if(value < min || value > max) {
    std::string reason("Invalid Value: ");
    reason += what;
    reason += " = " + boost::lexical_cast<std::string>(value);
    reason += ", should be in the range [";
    reason += boost::lexical_cast<std::string>(min);
    reason += ',';
    reason += boost::lexical_cast<std::string>(max);
    reason += ']';
    throw InvalidValue(reason);
  }
}

template <typename T>
void local::assertMin(std::string const &what, T value, T min) {
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
void local::assertMax(std::string const &what, T value, T max) {
  if(value > max) {
    std::string reason("Invalid Value: ");
    reason += what;
    reason += " = " + boost::lexical_cast<std::string>(value);
    reason += ", should be <= ";
    reason += boost::lexical_cast<std::string>(max);
    throw InvalidValue(reason);
  }
}

// explicit template instantiations for int, double args

template void local::assertRange<int>(std::string const&,int,int,int);
template void local::assertRange<double>(std::string const&,double,double,double);

template void local::assertMin<int>(std::string const&,int,int);
template void local::assertMin<double>(std::string const&,double,double);

template void local::assertMax<int>(std::string const&,int,int);
template void local::assertMax<double>(std::string const&,double,double);

// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/GenericPixelFunction.h"

namespace local = imengine;

local::GenericPixelFunction::GenericPixelFunction() :
AbsPixelFunction()
{ }

local::GenericPixelFunction::~GenericPixelFunction() { }

void local::GenericPixelFunction::fillArrayWithTransform(double **array, int ngrid,
double spacing, double dx, double dy) const {
    return;
}
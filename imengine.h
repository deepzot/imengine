// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE
#define IMENGINE

// Includes all package headers with public APIs...

// Fourier transform implementations
#include "imengine/TransformData.h"
#include "imengine/FastTransformData.h"

// Pixel interpolation schemes
#include "imengine/MidpointImageEngine.h"
#include "imengine/BilinearImageEngine.h"
#include "imengine/BicubicImageEngine.h"

// Source and PSF models
#include "imengine/models/DiskDemo.h"
#include "imengine/models/GaussianDemo.h"

// Image writers
#include "imengine/ImageWriter.h"
#include "imengine/ImageFileWriter.h"

#endif // IMENGINE
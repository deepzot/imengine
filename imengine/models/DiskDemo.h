// Created 11-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_DISK_DEMO
#define IMENGINE_MODELS_DISK_DEMO

#include "imengine/GenericPixelFunction.h"

namespace imengine {
namespace models {
	class DiskDemo : public GenericPixelFunction {
	public:
		DiskDemo(double size);
		virtual ~DiskDemo();
		// Returns the function value
        virtual double operator()(double x, double y) const;
	private:
        double _size,_sizesq,_invnorm;
	}; // DiskDemo
}} // imengine::models

#endif // IMENGINE_MODELS_DISK_DEMO

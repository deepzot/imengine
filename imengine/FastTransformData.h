// Created 18-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_FAST_TRANSFORM_DATA
#define IMENGINE_FAST_TRANSFORM_DATA

#include "imengine/TransformData.h"

namespace imengine {
	class FastTransformData : public TransformData {
	public:
		FastTransformData(int gridSize, double gridSpacing);
		virtual ~FastTransformData();
		// Creates a new transform data object with attributes copied from the specified prototype
		static FastTransformData *createFromPrototype(DataGrid const& prototype);
	private:
	}; // FastTransformData
} // imengine

#endif // IMENGINE_FAST_TRANSFORM_DATA

// Created 02-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_PTR_TYPES
#define IMENGINE_PTR_TYPES

#include "boost/smart_ptr.hpp"

namespace imengine {

    class AbsPixelFunction;
    class InterpolationData;
    class TransformData;
    class AbsCoordTransform;
    class AbsRadialProfile;
    class AbsImageEngine;
    class AbsImageWriter;
    class Observer;
    
    typedef boost::shared_ptr<AbsPixelFunction> AbsPixelFunctionPtr;
    typedef boost::shared_ptr<InterpolationData> InterpolationDataPtr;
    typedef boost::shared_ptr<TransformData> TransformDataPtr;
    typedef boost::shared_ptr<AbsCoordTransform> AbsCoordTransformPtr;
    typedef boost::shared_ptr<AbsRadialProfile> AbsRadialProfilePtr;
    typedef boost::shared_ptr<AbsImageEngine> AbsImageEnginePtr;
    typedef boost::shared_ptr<AbsImageWriter> AbsImageWriterPtr;
    typedef boost::shared_ptr<Observer> ObserverPtr;

} // imengine

#endif // IMENGINE_PTR_TYPES
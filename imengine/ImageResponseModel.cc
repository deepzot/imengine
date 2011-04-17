// Created 26-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ImageResponseModel.h"
#include "imengine/InvalidValue.h"

#include "boost/random/poisson_distribution.hpp"
#include "boost/random/normal_distribution.hpp"
#include "boost/random/variate_generator.hpp"

namespace local = imengine;

local::ImageResponseModel::ImageResponseModel(AbsImageWriterPtr writer,
double total, double offset, double gain, double noiseRMS, uint32_t seed)
: AbsImageFilter(writer), _total(total), _offset(offset), _gain(gain), _noiseRMS(noiseRMS),
_uniform(seed)
{
    assertGreaterThan<double>("ImageResponseModel total",total,0);
    assertGreaterThanOrEqualTo<double>("ImageResponseModel gain",gain,0);
    assertGreaterThanOrEqualTo<double>("ImageResponseModel noiseRMS",noiseRMS,0);
    noise = boost::variate_generator<boost::mt19937&, boost::normal_distribution<> >
        (_uniform, boost::normal_distribution<>(0,_noiseRMS));
}

local::ImageResponseModel::~ImageResponseModel() { }

double local::ImageResponseModel::filter(int x, int y, double in) const {
    double out(_offset);
    // add the signal
    if(_gain > 0) {
        double mean(_total/_gain*in);
        boost::variate_generator<boost::mt19937&, boost::poisson_distribution<> >
            poisson(_uniform, boost::poisson_distribution<>(mean));
        out += _gain*poisson();
    }
    else {
        out += _total*in;
    }
    // add the noise
    if(_noiseRMS > 0) {
        out += noise();
    }
    return out;
}

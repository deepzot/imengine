// Created 26-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_IMAGE_RESPONSE_MODEL
#define IMENGINE_IMAGE_RESPONSE_MODEL

#include "imengine/AbsImageFilter.h"

#include "boost/random/mersenne_twister.hpp"
#include "boost/function.hpp"

namespace imengine {
	class ImageResponseModel : public AbsImageFilter {
	public:
	    // Transforms the input value according to out = offset + gain*poisson + noise
	    // where poisson is an integer sampled from a Poisson distribution with mean
	    // total/gain*in and noise is sampled from a Gaussian with the specified RMS.
	    // Note that the input values are assumed to be normalized for the Poisson model.
	    // Transformed values are passed to the specified writer. Use gain=0 to disable
	    // Poisson fluctuations or noiseRMS=0 to disable Gaussian fluctuations.
		ImageResponseModel(AbsImageWriterPtr writer,
		    double total, double offset, double gain, double noiseRMS, uint32_t seed = 2011);
		virtual ~ImageResponseModel();
        // Filters each pixel before writing it by applying our response model.
        virtual double filter(int x, int y, double value) const;
        // Returns a random noise value sampled from a Gaussian distribution.
        boost::function<double ()> noise;
        // Sets the seed for generating subsequent random numbers.
        void setSeed(uint32_t seedValue);
	private:
        double _total, _offset, _gain, _noiseRMS;
        mutable boost::mt19937 _uniform;
	}; // ImageResponseModel
	
	inline void ImageResponseModel::setSeed(uint32_t seedValue) {
        _uniform.seed(seedValue);
	}
	
} // imengine

#endif // IMENGINE_IMAGE_RESPONSE_MODEL

// Created 8-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include <iostream>
#include <sys/resource.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include "imengine.h"

namespace img = imengine;
namespace mod = imengine::models;

// Returns the number of elapsed microseconds from before to after.
double elapsed(struct timeval const &before, struct timeval const &after) {
    return (after.tv_sec - before.tv_sec)*1e6 + (after.tv_usec - before.tv_usec);
}
double elapsed(struct rusage const &before, struct rusage const &after) {
    return elapsed(before.ru_utime,after.ru_utime) + elapsed(before.ru_stime,after.ru_stime);
}

// initialize random number generator
boost::mt19937 gen;
boost::uniform_real<> pdf(-1,+1);
boost::variate_generator<boost::mt19937&, boost::uniform_real<> > offset(gen, pdf);

// initialize array image writers
img::ArrayImageWriter slowResult,fastResult;

double trial(int scaleUp, int trials, bool slow) {
    // initialize the models
    mod::DiskDemo src(scaleUp);
    mod::GaussianDemo psf(scaleUp);
    // create a fast/slow bilinear engine
    img::AbsImageEngine *engine = slow ?
        (img::AbsImageEngine*)(new img::BilinearImageEngine<img::SlowTransform>(src,psf,6*scaleUp,1)) :
        (img::AbsImageEngine*)(new img::BilinearImageEngine<img::FastTransform>(src,psf,6*scaleUp,1));
    // run the engine once with no offset to trigger first-time initializations
    img::ArrayImageWriter &writer = slow ? slowResult : fastResult;
    engine->generate(writer,0,0);
    // use a silent image writer for the trials
    img::SilentImageWriter silent;
    // run timed trials with the slow engine
    double sum(0),sumsq(0);
    struct rusage before,after;
    getrusage(RUSAGE_SELF,&before);
    for(int n = 0; n < trials; n++) {
        // generate an image with a dx,dy offsets
        engine->generate(silent,offset(),offset());
    }
    getrusage(RUSAGE_SELF,&after);
    // clean up
    delete engine;
    // return the average trial time in usecs
    return elapsed(before,after)/trials;    
}

int main(int argc, char **argv) {
    
    std::cout << "6 " << trial(1,10000,true) << ' ' << trial(1,10000,false) << std::endl;
    std::cout << "12 " << trial(2,3000,true) << ' ' << trial(2,1000,false) << std::endl;
    std::cout << "24 " << trial(4,200,true) << ' ' << trial(4,1000,false) << std::endl;
    std::cout << "48 " << trial(8,15,true) << ' ' << trial(8,1000,false) << std::endl;
    std::cout << "96 " << trial(16,1,true) << ' ' << trial(16,1000,false) << std::endl;
    /* only use fast method for larger grid sizes */
    std::cout << "96 0 " << trial(16,1000,false) << std::endl;
    std::cout << "192 0 " << trial(32,1000,false) << std::endl;
    std::cout << "384 0 " << trial(64,100,false) << std::endl;
    std::cout << "768 0 " << trial(128,100,false) << std::endl;
    std::cout << "1536 0 " << trial(256,100,false) << std::endl;
}

/* results on DK laptop:
6 640.7 11.0685
12 7501.21 34.632
24 101350 138.41
48 1.48939e+06 785.7
96 2.27998e+07 5173
*/
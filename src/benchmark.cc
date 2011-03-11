// Created 8-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include <iostream>
#include <cmath>
#include <math.h> // for erf
#include <sys/resource.h>

#include <boost/smart_ptr.hpp>
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
boost::uniform_real<> pdf(-0.5,+0.5);
boost::variate_generator<boost::mt19937&, boost::uniform_real<> > offset(gen, pdf);

// initialize array image writers
img::ArrayImageWriter slowResult,fastResult,profileResult;

void checkResults(bool verbose = true, double abstol = 1e-14, double reltol = 1e-7) {
    std::cout << "Comparing fast and slow methods:" << std::endl;
    img::compareImages(slowResult,fastResult,verbose,abstol,reltol);
    std::cout << "Comparing fast and profile methods:" << std::endl;
    img::compareImages(fastResult,profileResult,verbose,abstol,reltol);
}

struct TrialResults {
    double speed,mean,rms;
};

std::ostream& operator<<(std::ostream& os, TrialResults const& results) {
    return os << ' ' << results.speed << ' ' << results.mean << ' ' << results.rms;
}

TrialResults trial(int scaleUp, int trials, bool slow, bool profile) {
    // prepare our results
    TrialResults results;

    // initialize the models
    img::AbsPixelFunctionPtr src,psf;
    double sigma(scaleUp/2.);
    if(profile) {
        img::AbsCoordTransformPtr identity(new img::IdentityTransform());
        img::AbsRadialProfilePtr gauss(new mod::GaussianProfile(sigma));
        src.reset(new img::TransformedProfileFunction(gauss,identity));
        psf.reset(new img::TransformedProfileFunction(gauss,identity));
    }
    else {
        src.reset(new mod::GaussianDemo(sigma));
        psf.reset(new mod::GaussianDemo(sigma));
    }

    // create a fast/slow bilinear engine
    img::AbsImageEngine *engine = slow ?
        (img::AbsImageEngine*)(new img::BilinearImageEngine<img::SlowTransform>(src,psf)) :
        (img::AbsImageEngine*)(new img::BilinearImageEngine<img::FastTransform>(src,psf));

    // initialize the engine
    engine->initialize(6*scaleUp,1);

    // run the engine once with a fixed offset, for comparing results between methods
    img::ArrayImageWriter *writer;
    if(slow) {
        writer = &slowResult;
    }
    else if(profile) {
        writer = &profileResult;
    }
    else {
        writer = &fastResult;
    }
    engine->generate(*writer,+0.1*scaleUp,-0.2*scaleUp);

    // use a silent image writer for the timing trials
    img::SilentImageWriter silent;
    // run timed trials with the slow engine
    double norm;
    long double nsum(0),nsumsq(0);
    struct rusage before,after;
    getrusage(RUSAGE_SELF,&before);
    for(int n = 0; n < trials; n++) {
        // generate an image with dx,dy offsets
        double dx(offset()),dy(offset());
        double norm(engine->generate(silent,dx*scaleUp,dy*scaleUp));
        // calculate the analytic norm for these offsets
        double analyticNorm = (erf(3 - dx) + erf(3 + dx))*(erf(3 - dy) + erf(3 + dy))/4.;
        ////std::cout << slow << ',' << profile << ' ' << analyticNorm << ' ' << norm << std::endl;
        double delta(norm - analyticNorm);
        nsum += delta;
        nsumsq += delta*delta;
    }
    // calculate the average trial time in usecs
    getrusage(RUSAGE_SELF,&after);
    results.speed = elapsed(before,after)/trials;
    // calculate the mean and rms normalization
    nsum /= trials;
    nsumsq /= trials;
    results.mean = (double)nsum;
    results.rms = (nsumsq > nsum*nsum) ? (double)std::sqrt(nsumsq - nsum*nsum) : 0;
    // clean up
    delete engine;
    return results;
}

int main(int argc, char **argv) {
    
    // use both fast and slow methods for small grid sizes and check that their results agree
    std::cout << "6" << trial(1,10000,true,false) << trial(1,10000,false,false) << trial(1,10000,false,true) << std::endl;
    checkResults();
    std::cout << "12" << trial(2,3000,true,false) << trial(2,1000,false,false) << trial(2,1000,false,true) << std::endl;
    checkResults();
    std::cout << "24" << trial(4,200,true,false) << trial(4,1000,false,false) << trial(4,1000,false,true) << std::endl;
    checkResults();
    std::cout << "48" << trial(8,15,true,false) << trial(8,1000,false,false) << trial(8,1000,false,true) << std::endl;
    checkResults();
    
    /* only use fast method for larger grid sizes */
    std::cout << "96 0 0 0" << trial(16,1000,false,false) << trial(16,1000,false,true) << std::endl;
    std::cout << "192 0 0 0" << trial(32,1000,false,false) << trial(32,1000,false,true) << std::endl;
    std::cout << "384 0 0 0" << trial(64,100,false,false) << trial(64,100,false,true) << std::endl;
    std::cout << "768 0 0 0" << trial(128,100,false,false) << trial(128,100,false,true) << std::endl;
    std::cout << "1536 0 0 0" << trial(256,100,false,false) << trial(256,100,false,true) << std::endl;
}

/* results on DK laptop:

6 711.577 0.15823 0.0385584 18.3093 0.158461 0.038165 15.347 0.00897842 0.00532983
12 8203.3 -7.06158e-05 2.87553e-05 61.425 -6.98165e-05 2.79078e-05 49.708 -7.17438e-05 3.00037e-05
24 110001 1.61521e-05 1.16178e-05 236.224 1.67233e-05 1.14251e-05 172.64 1.58772e-05 1.09837e-05
48 1.60816e+06 7.94458e-05 4.20257e-05 1031.82 6.86966e-05 3.50986e-05 701.809 6.50831e-05 3.48283e-05
96 0 0 0 5989.77 9.97817e-05 5.19691e-05 3594.41 9.99693e-05 5.1331e-05
192 0 0 0 23982.1 0.000116764 6.16052e-05 17625.9 0.000122502 6.32817e-05
384 0 0 0 73808.2 0.000136692 6.69746e-05 60293.8 0.000144312 7.47243e-05
768 0 0 0 406168 0.000135596 6.62343e-05 270899 0.000136592 7.12552e-05
1536 0 0 0 1.92218e+06 0.000133583 7.14895e-05 1.29252e+06 0.000154197 7.68557e-05

set log xy
set grid x
set grid y
plot '/tmp/bench.dat' using 1:2 with lines title 'slow', '/tmp/bench.dat' using 1:5 with lines title 'fast', '/tmp/bench.dat' using 1:8 with lines title 'profile'
plot '/tmp/bench.dat' using 1:(abs($6)) with lines title 'fast', '/tmp/bench.dat' using 1:(abs($9)) with lines title 'profile'

*/
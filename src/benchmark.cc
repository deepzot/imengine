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

void checkResults(bool verbose = false, double abstol = 1e-14, double reltol = 1e-8) {
    bool pass1 = img::compareImages(slowResult,fastResult,verbose,abstol,reltol);
    if(!pass1) {
        std::cout << "Fast and slow methods give different results!" << std::endl;
    }
    bool pass2 = img::compareImages(fastResult,profileResult,verbose,abstol,reltol);
    if(!pass2) {
        std::cout << "Fast and profile methods give different results!" << std::endl;
    }
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
        std::cout << slow << ',' << profile << ' ' << analyticNorm << ' ' << norm << std::endl;
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
    std::cout << "6" << trial(1,10000,true,false) << trial(1,10000,false,false) << std::endl;
    checkResults();
    std::cout << "12" << trial(2,3000,true,false) << trial(2,1000,false,false) << std::endl;
    checkResults();
    std::cout << "24" << trial(4,200,true,false) << trial(4,1000,false,false) << std::endl;
    checkResults();
    std::cout << "48" << trial(8,15,true,false) << trial(8,1000,false,false) << std::endl;
    checkResults();
    
    /* only use fast method for larger grid sizes */
    std::cout << "96 0 0 0" << trial(16,1000,false,false) << std::endl;
    std::cout << "192 0 0 0" << trial(32,1000,false,false) << std::endl;
    std::cout << "384 0 0 0" << trial(64,100,false,false) << std::endl;
    std::cout << "768 0 0 0" << trial(128,100,false,false) << std::endl;
    std::cout << "1536 0 0 0" << trial(256,100,false,false) << std::endl;
}

/* results on DK laptop:

-- midpoint --
6 375.4 0.0589314 7.14934e-05 12.4916 0.0589317 7.17383e-05
12 5698.33 0.000144701 7.23113e-05 45.007 0.000146114 7.22083e-05
24 89044.4 0.000144417 6.8416e-05 197.06 0.000138557 6.74034e-05
48 1.40468e+06 0.000168864 7.09367e-05 784.731 0.000144993 7.28755e-05
96 0 0 0 3093.22 0.000141672 7.18092e-05
192 0 0 0 13046.8 0.000140511 7.21483e-05
384 0 0 0 56434.9 0.000143047 7.50315e-05
768 0 0 0 239726 0.000134577 6.46979e-05
1536 0 0 0 1.01022e+06 0.000148855 7.11177e-05

-- bilinear --
6 652.589 0.0569047 0.00105429 15.933 0.0569038 0.00106223
12 7612.96 -7.11412e-05 2.95252e-05 55.089 -7.17597e-05 2.95167e-05
24 102526 1.67862e-05 1.08687e-05 210.382 1.58487e-05 1.06391e-05
48 1.49872e+06 7.94434e-05 3.5143e-05 934.909 6.77311e-05 3.59743e-05
96 0 0 0 5586.96 9.86419e-05 5.12471e-05
192 0 0 0 22627 0.000117522 6.10895e-05
384 0 0 0 69373 0.000130883 6.90625e-05
768 0 0 0 386075 0.00012872 6.20781e-05
1536 0 0 0 1.82254e+06 0.000145602 6.96621e-05

-- bicubic --
6 1750.52 0.0597253 0.000569863 27.5378 0.0597258 0.000575275
12 13359.2 0.000111292 3.35428e-05 78.217 0.000112044 3.35654e-05
24 139184 7.29969e-06 2.54761e-06 303.371 7.08296e-06 2.52345e-06
48 1.762e+06 1.83994e-05 8.65504e-06 1274.17 1.55573e-05 8.81381e-06
96 0 0 0 4387.38 4.73693e-05 2.5724e-05
192 0 0 0 16821.3 8.18845e-05 4.35842e-05
384 0 0 0 97604.7 0.000109442 5.84324e-05
768 0 0 0 411327 0.000117722 5.71324e-05
1536 0 0 0 1.40121e+06 0.000139296 6.68336e-05

*/
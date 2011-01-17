// Created 8-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include <iostream>
#include <sys/resource.h>

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

double trial(int scaleUp=1, int trials = 100) {
    // initialize the models
    mod::DiskDemo src(scaleUp);
    mod::GaussianDemo psf(scaleUp);
    img::BilinearImageEngine engine(src,psf,6*scaleUp,1);
    // run the engine once to trigger first-time initializations
    engine.generate();
    // run timed trials
    struct rusage before,after;
    getrusage(RUSAGE_SELF,&before);
    for(int n = 0; n < trials; n++) {
        engine.generate();
    }
    getrusage(RUSAGE_SELF,&after);
    // return the average trial time in usecs
    return elapsed(before,after)/trials;    
}

int main(int argc, char **argv) {
    std::cout << "6 " << trial(1,10000) << std::endl;
    std::cout << "12 " << trial(2,1000) << std::endl;
    std::cout << "24 " << trial(4,100) << std::endl;
    std::cout << "48 " << trial(8,10) << std::endl;
    std::cout << "96 " << trial(16,1) << std::endl;
}

/* results:
6 869.386
12 10387.2
24 141793
48 2.09801e+06
96 3.22019e+07
*/
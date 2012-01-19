// Created 18-Jan-2012 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include <iostream>

#include "imengine/imengine.h"

namespace img = imengine;
namespace mod = imengine::models;

int main(int argc, char **argv) {
    double sigma(1);
    mod::GaussianProfile src(sigma), psf(sigma);
    img::BilinearImageEngine<img::FastTransform> engine(src,psf);

    img::ArrayImageWriter stamp;
    int npix(48);
    double dx(0),dy(0);
    engine.initialize(npix);
    engine.generate(stamp,dx,dy);
}

// Created 8-Jan-2011 by David Kirkby <dkirkby@uci.edu>

#include "imengine/models/DiskDemo.h"
#include "imengine/models/GaussianDemo.h"
#include "imengine/BilinearImageEngine.h"

namespace img = imengine;
namespace mod = imengine::models;

int main(int argc, char **argv) {
    mod::DiskDemo src(5);
    mod::GaussianDemo psf(1);
    img::BilinearImageEngine engine(src,psf,25,0.75);
    engine.generate(0,0);
}

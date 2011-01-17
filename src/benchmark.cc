// Created 8-Jan-2011 by David Kirkby <dkirkby@uci.edu>

#include "imengine/models/DiskDemo.h"
#include "imengine/models/GaussianDemo.h"
#include "imengine/MidpointImageEngine.h"
#include "imengine/BilinearImageEngine.h"
#include "imengine/BicubicImageEngine.h"

namespace img = imengine;
namespace mod = imengine::models;

int main(int argc, char **argv) {
    mod::GaussianDemo src(1);
    mod::GaussianDemo psf(1);
    img::BilinearImageEngine engine(src,psf,10,3.0);
    engine.generate(0.5,0);
}

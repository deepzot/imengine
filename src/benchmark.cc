// Created 8-Jan-2011 by David Kirkby <dkirkby@uci.edu>

#include "imengine/models/DiskDemo.h"
#include "imengine/models/GaussianDemo.h"
#include "imengine/MidpointImageEngine.h"

namespace img = imengine;
namespace mod = imengine::models;

int main(int argc, char **argv) {
    mod::DiskDemo src(24);
    mod::GaussianDemo psf(8);
    img::MidpointImageEngine engine(src,psf,48);
    engine.generate();
}

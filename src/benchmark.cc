// Created 8-Jan-2011 by David Kirkby <dkirkby@uci.edu>

#include "imengine/models/GaussianDemo.h"
#include "imengine/MidpointImageEngine.h"

namespace img = imengine;
namespace models = imengine::models;

int main(int argc, char **argv) {
    models::GaussianDemo src(3),psf(3);
    img::MidpointImageEngine engine(src,psf,8);
    engine.generate();
}

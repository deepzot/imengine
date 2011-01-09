// Created 8-Jan-2011 by David Kirkby <dkirkby@uci.edu>

#include "imengine/model/CircularDisc.h"
#include "imengine/MidpointImageEngine.h"

namespace img = imengine;
namespace model = imengine::model;

int main(int argc, char **argv) {
    model::Disc disc(12);
    img::TransformedFunction src(disc);
    //model::Gaussian psf(...);
    img::ImageEngine *engine = new img::MidpointImageEngine(src,src,48);
    delete engine;
}

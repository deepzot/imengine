// Created 18-Jan-2012 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

// An example of generating an image via the C++ API, equivalent to the command:
// imgenerate -n 8 --src "exp[4]"

#include <iostream>

#include "imengine/imengine.h"

namespace img = imengine;
namespace mod = imengine::models;

int main(int argc, char **argv) {
    
    double re(4);
    int npix(8);
    double dx(0),dy(0);
    
    img::AbsPixelFunctionPtr src,psf;
    img::AbsCoordTransformPtr identity(new img::IdentityTransform());
    img::AbsRadialProfilePtr expProfile(new mod::ExponentialProfile(re));
    src.reset(new img::TransformedProfileFunction(expProfile,identity));
    //psf.reset(new img::TransformedProfileFunction(identity,identity));
    psf.reset(new mod::DeltaFunction());
    img::BilinearImageEngine<img::FastTransform> engine(src,psf);

    img::ArrayImageWriter stamp;
    engine.initialize(npix);
    engine.generate(stamp,dx,dy);
    
    for(int x = 0; x < npix; ++x) {
        for(int y = 0; y < npix; ++y) {
            std::cout << ' ' << stamp.getValue(x,y);
        }
        std::cout << std::endl;
    }
}

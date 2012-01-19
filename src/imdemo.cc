// Created 18-Jan-2012 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

// An example of generating an image via the C++ API, equivalent to the command:
// imgenerate -n 8 --src "exp[4]%{0.1,-0.2;-0.05,0}" --psf "moffat[2,3]%{0.02,-0.01}" --bilinear

#include <iostream>

#include "imengine/imengine.h"

namespace img = imengine;
namespace mod = imengine::models;

int main(int argc, char **argv) {
    
    // Define parameter values
    double re(4),fwhm(2),beta(3);
    int npix(8);
    double e1(0.1),e2(-0.2),g1(-0.05),g2(0),epsf1(0.02),epsf2(-0.01);
    double dx(0),dy(0);
    
    // Initialize the galaxy source model as a Sersic (n=1) radial profile
    // transformed by an intrinsic ellipticity (e1,e2) and weak-lensing shear (g1,g2)
    img::AbsRadialProfilePtr sersic(new mod::ExponentialProfile(re));
    img::AbsCoordTransformPtr shear(new img::EllipticityTransform(e1,e2,g1,g2));
    img::AbsPixelFunctionPtr source(new img::TransformedProfileFunction(sersic,shear));

    // Initialize the psf model as a Moffat radial profile sheared by (epsf1,epsf2)
    img::AbsRadialProfilePtr moffat(new mod::MoffatProfile(fwhm,beta));
    img::AbsCoordTransformPtr psfShear(new img::EllipticityTransform(epsf1,epsf2));
    img::AbsPixelFunctionPtr psf(new img::TransformedProfileFunction(moffat,psfShear));

    // Initialize the image engine
    img::BilinearImageEngine<img::FastTransform> engine(source,psf);
    engine.initialize(npix);

    // Generate and dump a postage stamp
    img::ArrayImageWriter stamp;
    engine.generate(stamp,dx,dy);
    for(int y = 0; y < npix; ++y) {
        for(int x = 0; x < npix; ++x) {
            std::cout << ' ' << stamp.getValue(x,y);
        }
        std::cout << std::endl;
    }
}

// Created 18-Jan-2012 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

// An example of generating an image via the C++ API, equivalent to the imgenerate command line below:
//
// ./imgenerate -n 48 --src "exp[12]%{0.1,-0.2;-0.05,0}" --psf "moffat[8,3]%{0.02,-0.01}" \
//     --dx 3.3 --dy -2.5 --bilinear -o stamp1.dat
//
// The identical output file should be produced by this program:
//
// ./imdemo > stamp2.dat
// diff stamp1.dat stamp2.dat

#include <iostream>

#include "imengine/imengine.h"

namespace img = imengine;
namespace mod = imengine::models;

int main(int argc, char **argv) {

    // Number of pixels along each side of the generated postage stamp
    int npix(48);
    // Sersic profile (n=1) half-light radius (pixels)
    double re(12);
    // Moffat profile fwhm (pixels) and beta parameter
    double fwhm(8),beta(3);
    // Galaxy intrinsic ellipticity (e1,e1) and shear (g1,g2)
    double e1(0.1),e2(-0.2),g1(-0.05),g2(0);
    // PSF shear
    double epsf1(0.02),epsf2(-0.01);
    // Galaxy offset (dx,dy) from postage stamp center (pixels)
    double dx(3.3),dy(-2.5);
    
    // Build a galaxy source model as a Sersic (n=1) radial profile
    // transformed by an intrinsic ellipticity (e1,e2) and weak-lensing shear (g1,g2)
    img::AbsRadialProfilePtr sersic(new mod::ExponentialProfile(re));
    img::AbsCoordTransformPtr srcShear(new img::EllipticityTransform(e1,e2,g1,g2));
    img::AbsPixelFunctionPtr source(new img::TransformedProfileFunction(sersic,srcShear));

    // Build a psf model as a Moffat radial profile sheared by (epsf1,epsf2)
    img::AbsRadialProfilePtr moffat(new mod::MoffatProfile(fwhm,beta));
    img::AbsCoordTransformPtr psfShear(new img::EllipticityTransform(epsf1,epsf2));
    img::AbsPixelFunctionPtr psf(new img::TransformedProfileFunction(moffat,psfShear));

    // Initialize an image engine for the requested model and stamp size
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

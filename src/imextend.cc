// Created 19-Jan-2012 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

// An example of extending imengine with a new model, equivalent to the imgenerate command line below:
//
// ./imgenerate -n 48 --src "sum[gdemo[4],gdemo[8];0.3,7.5,-4.5]" --psf "moffat[8,3]%{0.02,-0.01}" \
//     --bilinear -o stamp1.dat
//
// The identical output file should be produced by this program:
//
// ./imextend > stamp2.dat
// diff stamp1.dat stamp2.dat

#include <iostream>
#include <cmath>

#include "imengine/imengine.h"

namespace img = imengine;
namespace mod = imengine::models;

// Build a new 2D model based on the GenericPixelFunction class.
class MyGaussian : public img::GenericPixelFunction {
public:
    // Creates a new model with the specified sigma in pixels.
	MyGaussian(double sigma)
	: _twosigmasq(2*sigma*sigma), _norm(8*std::atan(1.0)*sigma*sigma)
	{ }
	// Returns the normalized function value at (x,y) in pixel space.
    double operator()(double x, double y) const {
        return std::exp(-(x*x+y*y)/_twosigmasq)/_norm;
    }
private:
    double _twosigmasq,_norm;
}; // MyGaussian

int main(int argc, char **argv) {

    // Number of pixels along each side of the generated postage stamp
    int npix(48);
    // Gaussian RMS values for the two source components.
    double sigma1(4), sigma2(8);
    // Fraction of flux in the core (sigma1) Gaussian.
    double frac(0.3);
    // Offset of the the tail (sigma2) Gaussian from the core in pixels.
    double dx(7.5), dy(-4.5);
    // Moffat profile fwhm (pixels) and beta parameter
    double fwhm(8),beta(3);
    // PSF shear
    double epsf1(0.02),epsf2(-0.01);
    
    // Build a galaxy source model the sum of two Gaussians with different RMS values.
    img::AbsPixelFunctionPtr core(new MyGaussian(sigma1)),tail(new MyGaussian(sigma2));
    img::AbsPixelFunctionPtr source(new img::PixelFunctionSum(core,tail,frac,dx,dy));

    // Build a psf model as a Moffat radial profile sheared by (epsf1,epsf2)
    img::AbsRadialProfilePtr moffat(new mod::MoffatProfile(fwhm,beta));
    img::AbsCoordTransformPtr psfShear(new img::EllipticityTransform(epsf1,epsf2));
    img::AbsPixelFunctionPtr psf(new img::TransformedProfileFunction(moffat,psfShear));

    // Initialize an image engine for the requested model and stamp size
    img::BilinearImageEngine<img::FastTransform> engine(source,psf);
    engine.initialize(npix);

    // Generate and dump a postage stamp
    img::ArrayImageWriter stamp;
    engine.generate(stamp);
    for(int y = 0; y < npix; ++y) {
        for(int x = 0; x < npix; ++x) {
            std::cout << ' ' << stamp.getValue(x,y);
        }
        std::cout << std::endl;
    }
}

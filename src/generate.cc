// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include <iostream>
#include <string>

#include "imengine.h"

#include "boost/program_options.hpp"

namespace img = imengine;
namespace mod = imengine::models;
namespace po = boost::program_options;

int main(int argc, char **argv) {
    // configure command-line options processing using the boost program_options library
    int npixels;
    double dx,dy,scale;
    std::string outfile;
    po::options_description cli;
    cli.add_options()
        ("help,h", "Prints this info and exit.")
        ("output,o", po::value<std::string>(&outfile)->default_value(""),
            "Output file for writing image data (defaults to stdout).")
        ("midpoint", "Uses the midpoint method for pixelization.")
        ("bilinear", "Uses bilinear interpolation for pixelization (this is the default).")
        ("bicubic", "Uses bicubic interpolation for pixelization.")
        ("slow", "Uses un-optimized discrete Fourier transforms.")
        ("npixels,n", po::value<int>(&npixels)->default_value(48),
            "Number of pixels per side for final square image.")
        ("dx",po::value<double>(&dx)->default_value(0.),"Horizontal source shift.")
        ("dy",po::value<double>(&dy)->default_value(0.),"Vertical source shift.")
        ("scale",po::value<double>(&scale)->default_value(1.),"Pixel scale.")
        ;

    // do the command line parsing now
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, cli), vm);
        po::notify(vm);
    }
    catch(std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    
    if(vm.count("help")) {
        std::cout << cli << std::endl;
        return 1;
    }
    bool slow(vm.count("slow"));
    bool midpoint(vm.count("midpoint")),bilinear(vm.count("bilinear")),bicubic(vm.count("bicubic"));
    int methods = vm.count("midpoint")+vm.count("bilinear")+vm.count("bicubic");
    if(methods == 0) {
        bilinear = true; // specifies default method
    }
    else if(methods != 1) {
        std::cerr << "Only one pixelization method can be specified (midpoint,bilinear,bicubic)"
            << std::endl;
        return 2;
    }
    if(npixels <= 0) {
        std::cerr << "Option npixels must have a positive value" << std::endl;
        return 3;
    }

    img::AbsImageEngine *engine(0);
    try {
        // create the source model
        mod::DiskDemo src(0.2*npixels);
    
        // create the psf model
        mod::GaussianDemo psf(0.1*npixels);
    
        // create the pixelization engine
        if(midpoint) {
            engine = slow ?
                (img::AbsImageEngine*)(new img::MidpointImageEngine<img::TransformData>(src,psf,npixels,scale)) :
                (img::AbsImageEngine*)(new img::MidpointImageEngine<img::FastTransformData>(src,psf,npixels,scale));
        }
        else if(bilinear) {
            engine = slow ?
                (img::AbsImageEngine*)(new img::BilinearImageEngine<img::TransformData>(src,psf,npixels,scale)) :
                (img::AbsImageEngine*)(new img::BilinearImageEngine<img::FastTransformData>(src,psf,npixels,scale));
        }
        else if(bicubic) {
            engine = slow ?
                (img::AbsImageEngine*)(new img::BicubicImageEngine<img::TransformData>(src,psf,npixels,scale)) :
                (img::AbsImageEngine*)(new img::BicubicImageEngine<img::FastTransformData>(src,psf,npixels,scale));
        }
    
        // generate the image
        img::ImageFileWriter writer(outfile.c_str());
        engine->generate(writer,dx,dy);
    }
    catch(std::exception const &e) {
        std::cerr << "Internal error while generating the image:" << std::endl
            << e.what() << std::endl;
        return -2;
    }    
    
    // cleanup and exit without error
    if(engine) delete engine;
    return 0;
}

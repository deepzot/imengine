// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include <iostream>

#include "imengine.h"

#include "boost/program_options.hpp"

namespace img = imengine;
namespace mod = imengine::models;
namespace po = boost::program_options;

int main(int argc, char **argv) {
    // configure command-line options processing using the boost program_options library
    int npixels;
    po::options_description cli;
    cli.add_options()
        ("help,h", "Prints this info and exit.")
        ("midpoint", "Uses the midpoint method for pixelization.")
        ("bilinear", "Uses bilinear interpolation for pixelization.")
        ("bicubic", "Uses bicubic interpolation for pixelization.")
        ("npixels,n", po::value<int>(&npixels)->default_value(48),
            "Number of pixels per side for final square image.");

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

    double scale = 1;

    // create the source model
    mod::DiskDemo src(0.2*npixels*scale);
    
    // create the psf model
    mod::GaussianDemo psf(0.1*npixels*scale);
    
    // create the pixelization engine
    img::ImageEngine *engine(0);
    if(midpoint) {
        engine = new img::MidpointImageEngine(src,psf,npixels,scale);
    }
    else if(bilinear) {
        engine = new img::BilinearImageEngine(src,psf,npixels,scale);
    }
    else if(bicubic) {
        engine = new img::BicubicImageEngine(src,psf,npixels,scale);
    }
    
    // generate the image
    engine->generate();
    
    // cleanup and exit without error
    if(engine) delete engine;
    return 0;
}

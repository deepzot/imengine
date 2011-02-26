// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include <iostream>
#include <string>

#include "imengine.h"

#include "boost/smart_ptr.hpp"
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
        ("profile", "Uses analytic profiles.")
        ("slow", "Uses un-optimized discrete Fourier transforms.")
        ("fast", "Uses optimized fast Fourier transforms.")
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
        std::cerr << "Unable to parse command line options: " << e.what() << std::endl;
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
    bool slow(vm.count("slow"));
    if(vm.count("slow")+vm.count("fast") > 1) {
        std::cerr << "Only one speed can be specified (fast,slow)" << std::endl;
        return 4;
    }
    bool profile(vm.count("profile"));

    boost::scoped_ptr<img::AbsImageEngine> engine;
    boost::scoped_ptr<img::AbsPixelFunction> src,psf;

    try {
        // create the source model
        double rdisk(0.205*npixels);
        if(profile) {
            boost::shared_ptr<img::AbsRadialProfile const> profile(new mod::DiskProfile(rdisk));
            boost::shared_ptr<img::AbsCoordTransform const> transform(new img::IdentityTransform);
            src.reset(new img::TransformedProfileFunction(profile,transform));            
        }
        else {
            src.reset(new mod::DiskDemo(rdisk));
        }
        //src.reset(new mod::DeltaFunction);
        
        // create the psf model
        double sigma(0.105*npixels);
        if(profile) {
            boost::shared_ptr<img::AbsRadialProfile const> profile(new mod::GaussianProfile(sigma));
            boost::shared_ptr<img::AbsCoordTransform const> transform(new img::IdentityTransform);
            psf.reset(new img::TransformedProfileFunction(profile,transform));
        }
        else {
            psf.reset(new mod::GaussianDemo(sigma));
        }
        psf.reset(new mod::DeltaFunction);
    
        // create the pixelization engine
        if(midpoint) {
            engine.reset(slow ?
                (img::AbsImageEngine*)(new img::MidpointImageEngine<img::SlowTransform>(*src,*psf)) :
                (img::AbsImageEngine*)(new img::MidpointImageEngine<img::FastTransform>(*src,*psf)));
        }
        else if(bilinear) {
            engine.reset(slow ?
                (img::AbsImageEngine*)(new img::BilinearImageEngine<img::SlowTransform>(*src,*psf)) :
                (img::AbsImageEngine*)(new img::BilinearImageEngine<img::FastTransform>(*src,*psf)));
        }
        else if(bicubic) {
            engine.reset(slow ?
                (img::AbsImageEngine*)(new img::BicubicImageEngine<img::SlowTransform>(*src,*psf)) :
                (img::AbsImageEngine*)(new img::BicubicImageEngine<img::FastTransform>(*src,*psf)));
        }
    
        // generate the image
        img::FileImageWriter writer(outfile.c_str());
        engine->initialize(npixels,scale);
        engine->generate(writer,dx,dy);
    }
    catch(std::exception const &e) {
        std::cerr << "Internal error while generating the image:" << std::endl
            << e.what() << std::endl;
        return -2;
    }    
    
    // cleanup and exit without error
    return 0;
}

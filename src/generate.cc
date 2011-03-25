// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include <iostream>
#include <string>

#include "imengine/imengine.h"

#include "boost/smart_ptr.hpp"
#include "boost/program_options.hpp"

namespace img = imengine;
namespace mod = imengine::models;
namespace po = boost::program_options;

int main(int argc, char **argv) {
    // configure command-line options processing using the boost program_options library
    int npixels;
    double dx,dy,scale;
    std::string outfile,srcString,psfString;
    po::options_description cli;
    cli.add_options()
        ("help,h", "Prints this info and exits.")
        ("output,o", po::value<std::string>(&outfile)->default_value(""),
            "Output file for writing image data (defaults to stdout).")
        ("png", "Writes a 16-bit grayscale png image.")
        ("midpoint", "Uses the midpoint method for pixelization.")
        ("bilinear", "Uses bilinear interpolation for pixelization (this is the default).")
        ("bicubic", "Uses bicubic interpolation for pixelization.")
        ("slow", "Uses un-optimized discrete Fourier transforms.")
        ("fast", "Uses optimized fast Fourier transforms (default).")
        ("npixels,n", po::value<int>(&npixels)->default_value(48),
            "Number of pixels per side for final square image.")
        ("dx",po::value<double>(&dx)->default_value(0.),"Horizontal source shift.")
        ("dy",po::value<double>(&dy)->default_value(0.),"Vertical source shift.")
        ("scale",po::value<double>(&scale)->default_value(1.),"Pixel scale.")
        ("src",po::value<std::string>(&srcString)->default_value("disk[1]"),"Source module to use.")
        ("psf",po::value<std::string>(&psfString)->default_value("gauss[1]"),"PSF module to use.")
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
    bool png(vm.count("png"));

    try {
        // create the source and psf models
        img::ModelBuilder builder;
        img::AbsPixelFunctionPtr src(builder.parse(srcString));
        if(0 == src.get()) {
            std::cerr << "Unable to parse source model specification '" << srcString
                << "'." << std::endl;
            return -2;
        }
        img::AbsPixelFunctionPtr psf(builder.parse(psfString));
        if(0 == src.get()) {
            std::cerr << "Unable to parse psf model specification '" << psfString
                << "'." << std::endl;
            return -2;
        }

        // create the pixelization engine
        boost::scoped_ptr<img::AbsImageEngine> engine;
        if(midpoint) {
            engine.reset(slow ?
                (img::AbsImageEngine*)(new img::MidpointImageEngine<img::SlowTransform>(src,psf)) :
                (img::AbsImageEngine*)(new img::MidpointImageEngine<img::FastTransform>(src,psf)));
        }
        else if(bilinear) {
            engine.reset(slow ?
                (img::AbsImageEngine*)(new img::BilinearImageEngine<img::SlowTransform>(src,psf)) :
                (img::AbsImageEngine*)(new img::BilinearImageEngine<img::FastTransform>(src,psf)));
        }
        else if(bicubic) {
            engine.reset(slow ?
                (img::AbsImageEngine*)(new img::BicubicImageEngine<img::SlowTransform>(src,psf)) :
                (img::AbsImageEngine*)(new img::BicubicImageEngine<img::FastTransform>(src,psf)));
        }

        // select an appropriate image writer
        boost::scoped_ptr<img::AbsImageWriter> writer;
        std::string pngend(".png");
        int outlen(outfile.length()),endlen(pngend.length());
        if(png || (outlen >= endlen && 0 == outfile.compare(outlen-endlen,endlen,pngend))) {
            writer.reset(new img::PngImageWriter(outfile));
        }
        else {
            writer.reset(new img::FileImageWriter(outfile));
        }

        // generate the image
        engine->initialize(npixels,scale);
        engine->generate(*writer,dx,dy);
    }
    catch(std::exception const &e) {
        std::cerr << "Internal error while generating the image:" << std::endl
            << e.what() << std::endl;
        return -3;
    }    
    
    // cleanup and exit without error
    return 0;
}

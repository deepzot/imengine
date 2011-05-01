// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include <iostream>
#include <string>
#include <ctime>

#include "imengine/imengine.h"

#include "boost/program_options.hpp"

namespace img = imengine;
namespace mod = imengine::models;
namespace po = boost::program_options;

int main(int argc, char **argv) {
    // configure command-line options processing using the boost program_options library
    int npixels,oversampling,margin;
    uint32_t seed;
    double dx,dy,scale,total,offset,gain,noiseRMS;
    std::string outfile,srcString,psfString;
    po::options_description cli;
    cli.add_options()
        ("help,h", "Prints this info and exits.")
        ("output,o", po::value<std::string>(&outfile)->default_value(""),
            "Output file for writing image data (defaults to stdout).")
        ("png", "Writes a 16-bit grayscale png image.")
        ("noninverted",
            "Any png image written will be non-inverted (default is inverted).")
        ("midpoint", "Uses the midpoint method for pixelization.")
        ("bilinear", "Uses bilinear interpolation for pixelization.")
        ("bicubic", "Uses bicubic interpolation for pixelization (this is the default).")
        ("slow", "Uses un-optimized discrete Fourier transforms.")
        ("fast", "Uses optimized fast Fourier transforms (default).")
        ("npixels,n", po::value<int>(&npixels)->default_value(48),
            "Number of pixels per side for final square image.")
        ("dx",po::value<double>(&dx)->default_value(0.),"Horizontal source shift.")
        ("dy",po::value<double>(&dy)->default_value(0.),"Vertical source shift.")
        ("scale",po::value<double>(&scale)->default_value(1.),"Pixel scale.")
        ("oversampling",po::value<int>(&oversampling)->default_value(1),
            "Divides each pixel into N x N subpixels.")
        ("margin",po::value<int>(&margin)->default_value(0),
            "Adds or subtracts a temporary margin when generating the image.")
        ("total",po::value<double>(&total)->default_value(1.),
            "Total pixel sum of generated image.")
        ("offset",po::value<double>(&offset)->default_value(0.),
            "Amount to offset generated pixel values by.")
        ("gain",po::value<double>(&gain)->default_value(0.),
            "Signal size per pixel to use for generating Poisson fluctuations.")
        ("noiseRMS",po::value<double>(&noiseRMS)->default_value(0.),
            "RMS of uncorrelated Gaussian noise to add to each pixel.")
        ("seed",po::value<uint32_t>(&seed)->default_value(0),
            "Random seed to use for generating noise (uses time of day if zero).")
        ("printsum","Prints the pixel sum of the generated image.")
        ("src",po::value<std::string>(&srcString)->default_value("delta"),
            "Source module to use.")
        ("psf",po::value<std::string>(&psfString)->default_value("delta"),
            "PSF module to use.")
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
        bicubic = true; // specifies default method
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
    if(npixels + 2*margin <= 0) {
        std::cerr << "The requested negative margin (" << margin <<
            ") is too large for npixels = " << npixels << std::endl;
        return 3;
    }
    bool slow(vm.count("slow"));
    if(vm.count("slow")+vm.count("fast") > 1) {
        std::cerr << "Only one speed can be specified (fast,slow)" << std::endl;
        return 4;
    }
    if(oversampling < 1) {
        std::cerr << "Option oversampling must have a value > 0" << std::endl;
        return 5;
    }
    if(total <= 0) {
        std::cerr << "Option total must have a value > 0" << std::endl;
        return 6;
    }
    if(gain < 0) {
        std::cerr << "Option gain must have a value >= 0" << std::endl;
        return 6;
    }
    if(noiseRMS < 0) {
        std::cerr << "Option noiseRMS must have a value >= 0" << std::endl;
        return 6;
    }
    bool png(vm.count("png")),noninverted(vm.count("noninverted"));

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
        img::AbsImageEnginePtr engine;
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

        // use oversampling?
        if(oversampling > 1) {
            // original engine shared ptr is kept alive by the new oversampling engine
            engine.reset(new img::OversamplingImageEngine(engine,oversampling));
        }
        
        // add/subtract a margin?
        if(margin != 0) {
            // original engine shared ptr is kept alive by the new oversampling engine
            engine.reset(new img::ResizingImageEngine(engine,margin));
        }

        // select an appropriate image writer
        img::AbsImageWriterPtr writer;
        std::string pngend(".png");
        int outlen(outfile.length()),endlen(pngend.length());
        if(png || (outlen >= endlen && 0 == outfile.compare(outlen-endlen,endlen,pngend))) {
            writer.reset(new img::PngImageWriter(outfile,!noninverted));
        }
        else {
            writer.reset(new img::FileImageWriter(outfile));
        }

        // Select a random number seed for generating noise based on either the
        // current time or else specified on the command line.
        if(0 == seed) seed = static_cast<uint32_t>(std::time(0));

        // filter the image with the specified response model
        writer.reset(new img::ImageResponseModel(writer,total,offset,gain,noiseRMS,seed));

        // generate the image
        engine->initialize(npixels,scale);
        double sum(engine->generate(*writer,dx,dy));
        if(vm.count("printsum")) {
            std::cout << "sum = " << sum << std::endl;
        }
    }
    catch(std::exception const &e) {
        std::cerr << "Internal error while generating the image:" << std::endl
            << e.what() << std::endl;
        return -3;
    }    
    
    // cleanup and exit without error
    return 0;
}

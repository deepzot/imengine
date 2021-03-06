// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ModelBuilder.h"

#include "imengine/AbsPixelFunction.h"
#include "imengine/PixelFunctionSum.h"
#include "imengine/models/DeltaFunction.h"
#include "imengine/models/GaussianDemo.h"
#include "imengine/models/SersicDemo.h"
#include "imengine/models/DiskDemo.h"
#include "imengine/models/AiryDemo.h"
#include "imengine/TransformedProfileFunction.h"

#include "imengine/AbsRadialProfile.h"
#include "imengine/models/MoffatProfile.h"
#include "imengine/models/ExponentialProfile.h"
#include "imengine/models/GaussianProfile.h"
#include "imengine/models/DiskProfile.h"

#include "imengine/AbsCoordTransform.h"
#include "imengine/IdentityTransform.h"
#include "imengine/EllipticityTransform.h"
#include "imengine/PolarEllipticityTransform.h"

#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/qi.hpp"
#include "boost/spirit/include/phoenix_core.hpp"
#include "boost/spirit/include/phoenix_operator.hpp"

#include "boost/spirit/home/phoenix/object/construct.hpp" // better path to use?
#include "boost/spirit/home/phoenix/object/new.hpp" // better path to use?

#include <iostream>

namespace local = imengine;

namespace img = imengine;
namespace mod = imengine::models;
namespace qi = boost::spirit::qi;

namespace imengine {
namespace parser {
    
    template <typename Iterator>
    struct Grammar : qi::grammar<Iterator, AbsPixelFunctionPtr()>
    {
        Grammar() : Grammar::base_type(model), identity(new img::IdentityTransform)
        {
            using qi::lit;
            using qi::_val;
            using qi::_a;
            using qi::_b;
            using qi::_c;
            using qi::_d;
            using qi::_e;
            using qi::_f;
            using qi::_g;
            using qi::_1;
            using qi::_2;
            using qi::_3;
            using qi::_4;
            using qi::_5;
            using qi::double_;
            using boost::phoenix::construct;
            using boost::phoenix::new_;
            using boost::shared_ptr;
            
            model
                = ("sum[" >> model >> ',' >> model >> ';' >> double_ >> ']')
                    [_val = construct<AbsPixelFunctionPtr>
                        (new_<img::PixelFunctionSum>(_1,_2,_3))]
                | ("sum[" >> model >> ',' >> model >> ';' >> double_ >> ','
                    >> double_ >> ',' >> double_ >> ']')
                    [_val = construct<AbsPixelFunctionPtr>
                        (new_<img::PixelFunctionSum>(_1,_2,_3,_4,_5))]
                | standalone
                    [_val = _1]
                | (profile >> transform)
                    [_val = construct<AbsPixelFunctionPtr>
                    (new_<img::TransformedProfileFunction>(_1,_2))]
                | profile // use the identity transform by default
                    [_val = construct<AbsPixelFunctionPtr>
                    (new_<img::TransformedProfileFunction>(_1,identity))];
            
            // radial profile coordinate transformations
            transform = ellipticity2 | ellipticity4 | polar2 | polar4;
            ellipticity2 = ("%{" >> double_[_a=_1] >> ',' >> double_[_b=_1] >> '}')
                [_val = construct<AbsCoordTransformPtr>(
                new_<img::EllipticityTransform>(_a,_b))];
            ellipticity4 = ("%{" >> double_[_a=_1] >> ',' >> double_[_b=_1] >> ';'
                >> double_[_c=_1] >> ',' >> double_[_d=_1] >> '}')
                [_val = construct<AbsCoordTransformPtr>(
                new_<img::EllipticityTransform>(_a,_b,_c,_d))];
            polar2 = ("%<" >> double_[_a=_1] >> ',' >> double_[_b=_1] >> '>')
                [_val = construct<AbsCoordTransformPtr>(
                new_<img::PolarEllipticityTransform>(_a,_b))];
            polar4 = ("%<" >> double_[_a=_1] >> ',' >> double_[_b=_1] >> ';'
                >> double_[_c=_1] >> ',' >> double_[_d=_1] >> '>')
                [_val = construct<AbsCoordTransformPtr>(
                new_<img::PolarEllipticityTransform>(_a,_b,_c,_d))];

            // radial profile primitives
            profile = gauss | disk | exp | moffat;
            gauss = ("gauss[" >> double_[_a=_1] >> ']')
                [_val = construct<AbsRadialProfilePtr>(new_<mod::GaussianProfile>(_a))];
            disk = ("disk[" >> double_[_a=_1] >> ']')
                [_val = construct<AbsRadialProfilePtr>(new_<mod::DiskProfile>(_a))];
            exp = ("exp[" >> double_[_a=_1] >> ']')
                [_val = construct<AbsRadialProfilePtr>(new_<mod::ExponentialProfile>(_a))];
            moffat = ("moffat[" >> double_[_a=_1] >> ',' >> double_[_b=_1] >> ']')
                [_val = construct<AbsRadialProfilePtr>(new_<mod::MoffatProfile>(_a,_b))];
                
            // standalone pixel functions
            standalone = delta | gdemo | ddemo | sdemo2 | sdemo4 | sdemo5 | sdemo7 | ademo | ademo3;
            delta = lit("delta")
                [_val = construct<AbsPixelFunctionPtr>(new_<mod::DeltaFunction>())];
            gdemo = ("gdemo[" >> double_[_a=_1] >> ']')
                [_val = construct<AbsPixelFunctionPtr>(new_<mod::GaussianDemo>(_a))];
            ddemo = ("ddemo[" >> double_[_a=_1] >> ']')
                [_val = construct<AbsPixelFunctionPtr>(new_<mod::DiskDemo>(_a))];
            sdemo2 = ("sdemo[" >> double_[_a=_1] >> ',' >> double_[_b=_1] >> ']')
                [_val = construct<AbsPixelFunctionPtr>(new_<mod::SersicDemo>(_a,_b,0,0,0))];
            sdemo4 = ("sdemo[" >> double_[_a=_1] >> ',' >> double_[_b=_1] >> ','
                >> double_[_c=_1] >> ',' >> double_[_d=_1] >> ']')
                [_val = construct<AbsPixelFunctionPtr>(new_<mod::SersicDemo>(_a,_b,_c,_d,0))];
            sdemo5 = ("sdemo[" >> double_[_a=_1] >> ',' >> double_[_b=_1] >> ','
                >> double_[_c=_1] >> ',' >> double_[_d=_1] >> ',' >> double_[_e=_1] >> ']')
                [_val = construct<AbsPixelFunctionPtr>(new_<mod::SersicDemo>(_a,_b,_c,_d,_e))];
            sdemo7 = ("sdemo[" >> double_[_a=_1] >> ',' >> double_[_b=_1] >> ','
                >> double_[_c=_1] >> ',' >> double_[_d=_1] >> ',' >> double_[_e=_1] >> ','
                >> double_[_f=_1] >> ',' >> double_[_g=_1] >> ']')
                [_val = construct<AbsPixelFunctionPtr>(new_<mod::SersicDemo>(_a,_b,_c,_d,_e,_f,_g))];
            ademo = ("ademo[" >> double_[_a=_1] >> ']')
                [_val = construct<AbsPixelFunctionPtr>(new_<mod::AiryDemo>(_a,0,0))];
            ademo3 = ("ademo[" >> double_[_a=_1] >> ',' >> double_[_b=_1] >> ','
                >> double_[_c=_1] >> ']')
                [_val = construct<AbsPixelFunctionPtr>(new_<mod::AiryDemo>(_a,_b,_c))];
        }

        AbsCoordTransformPtr identity;

        qi::rule<Iterator, img::AbsPixelFunctionPtr()> model;
        qi::rule<Iterator, img::AbsPixelFunctionPtr()> standalone,delta;
        qi::rule<Iterator, img::AbsPixelFunctionPtr(), qi::locals<double> > gdemo,ddemo,ademo;
        qi::rule<Iterator, img::AbsPixelFunctionPtr(),
            qi::locals<double,double> > sdemo2;
        qi::rule<Iterator, img::AbsPixelFunctionPtr(),
            qi::locals<double,double,double> > ademo3;
        qi::rule<Iterator, img::AbsPixelFunctionPtr(),
            qi::locals<double,double,double,double> > sdemo4;
        qi::rule<Iterator, img::AbsPixelFunctionPtr(),
            qi::locals<double,double,double,double,double> > sdemo5;
        qi::rule<Iterator, img::AbsPixelFunctionPtr(),
            qi::locals<double,double,double,double,double,double,double> > sdemo7;
        qi::rule<Iterator, img::AbsCoordTransformPtr()> transform;
        qi::rule<Iterator, img::AbsCoordTransformPtr(),
            qi::locals<double,double> > ellipticity2,polar2;
        qi::rule<Iterator, img::AbsCoordTransformPtr(),
            qi::locals<double,double,double,double> > ellipticity4,polar4;
        qi::rule<Iterator, img::AbsRadialProfilePtr()> profile;
        qi::rule<Iterator, img::AbsRadialProfilePtr(), qi::locals<double> > gauss,disk,exp;
        qi::rule<Iterator, img::AbsRadialProfilePtr(), qi::locals<double,double> > moffat;
    };
    
}} // imengine::parser

local::ModelBuilder::ModelBuilder() { }

local::ModelBuilder::~ModelBuilder() { }

local::AbsPixelFunctionPtr local::ModelBuilder::parse(std::string const &input) {

    //std::cout << "ModelBuilder::parsing '" << input << "'..." << std::endl;

    typedef std::string::const_iterator iterator_type;
    iterator_type iter(input.begin()),end(input.end());
    img::parser::Grammar<iterator_type> parser;
    AbsPixelFunctionPtr result;

    bool ok = qi::parse(iter, end, parser, result);

    if(!ok || iter != end) {
        std::cerr << "ModelBuilder::parse: error!" << std::endl;
        result.reset();
    }
    return result;
}

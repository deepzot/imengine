// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/ModelBuilder.h"

#include "imengine/AbsPixelFunction.h"
#include "imengine/TransformedProfileFunction.h"
#include "imengine/models/MoffatProfile.h"
#include "imengine/models/ExponentialProfile.h"
#include "imengine/models/GaussianProfile.h"
#include "imengine/models/DiskProfile.h"
#include "imengine/models/DeltaFunction.h"

#include "imengine/IdentityTransform.h"
#include "imengine/EllipticityTransform.h"

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
    struct Grammar : qi::grammar<Iterator, boost::shared_ptr<img::AbsRadialProfile>()>
    {
        Grammar() : Grammar::base_type(profile)
        {
            using qi::lit;
            using qi::_val;
            using qi::_a;
            using qi::_b;
            using qi::_1;
            using qi::double_;
            using boost::phoenix::construct;
            using boost::phoenix::new_;
            using boost::shared_ptr;
            
            profile %= gauss;
            
            gauss = ("gauss[" >> double_[_a=_1] >> ']')
                [_val = construct<shared_ptr<img::AbsRadialProfile> >(new_<mod::GaussianProfile>(_a))];
        }
        double arg1,arg2;
        qi::rule<Iterator, boost::shared_ptr<img::AbsRadialProfile>()> profile;
        qi::rule<Iterator, boost::shared_ptr<img::AbsRadialProfile>(), qi::locals<double> >
            gauss;
    };
    
}} // imengine::parser

local::ModelBuilder::ModelBuilder() { }

local::ModelBuilder::~ModelBuilder() { }

boost::shared_ptr<img::AbsRadialProfile> local::ModelBuilder::parse(std::string const &input) {

    std::cout << "ModelBuilder::parsing '" << input << "'..." << std::endl;

    typedef std::string::const_iterator iterator_type;
    iterator_type iter(input.begin()),end(input.end());
    img::parser::Grammar<iterator_type> parser;
    boost::shared_ptr<img::AbsRadialProfile> result;

    bool ok = qi::parse(iter, end, parser, result);

    if(!ok || iter != end) result.reset();
    return result;
}

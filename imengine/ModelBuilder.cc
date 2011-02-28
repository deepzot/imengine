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

#include "boost/spirit/include/qi.hpp"
#include "boost/spirit/include/phoenix_core.hpp"
#include "boost/spirit/include/phoenix_operator.hpp"

namespace local = imengine;
namespace models = imengine::models;
namespace qi = boost::spirit::qi;

local::ModelBuilder::ModelBuilder() { }

local::ModelBuilder::~ModelBuilder() { }

boost::shared_ptr<local::AbsPixelFunction> local::ModelBuilder::parse(std::string const &input) {

    boost::shared_ptr<AbsPixelFunction> model;
    double arg1,arg2;

    using boost::spirit::qi::double_;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::_1;
    using boost::phoenix::ref;

    bool ok = qi::phrase_parse(input.begin(),input.end(),
        // --- begin grammar --------------
        (
            "gauss[" >> double_[ref(arg1) = _1] >> ']'
            //[model.reset((AbsPixelFunction*)(new models::GaussianProfile(_1)))]
        ),
        // --- end grammar ----------------
        boost::spirit::ascii::space);
    
    // return an empty model pointer if the parser failed
    if(!ok /*|| begin != input.end()*/) {
        model.reset();
        return model;
    }
    
    model.reset(new models::DeltaFunction);
    return model;
}

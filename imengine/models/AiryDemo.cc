// Created 22-Aug-2011 by Daniel Margala (University of California, Irvine) <dmargala@uci.edu>

#include "imengine/models/AiryDemo.h"
#include "imengine/InvalidValue.h"

#include <cmath>

namespace local = imengine::models;

local::AiryDemo::AiryDemo(double fwhm, double e1, double e2) :
GenericPixelFunction(), _initialized(false), _transform(e1,e2,0,0)
{
	_transform.setObserver(getObserver());
    setParameters(fwhm, e1, e2);
}

void local::AiryDemo::setParameters(double fwhm, double e1, double e2) {
	_transform.setParameters(e1,e2,0,0);
    if(_initialized && _fwhm == fwhm) return;
    assertGreaterThan<double>("AiryProfile fwhm",fwhm,0);
    _fwhm = fwhm;
	_rd = _fwhm/(2*AiryConst);
    _norm = _rd*_rd*NormConst;
    setChanged();
}

local::AiryDemo::~AiryDemo() { }

double local::AiryDemo::sinc(const double x) const{
	if(x == 0) {
		return 1;
	}
	else {
		return sin(x)/x;
	}
}

double local::AiryDemo::operator()(double x, double y) const {
    double r(_transform.transformedRadius(x,y));
    double rr = r/_rd;
    if(rr <= 1){
    	return sinc(rr)*sinc(rr)/_norm;
    }
    else {
    	return sinc(rr)*sinc(rr)/(_norm*rr);
    }
}

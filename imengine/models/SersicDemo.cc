// Created 17-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/SersicDemo.h"
#include "imengine/InvalidValue.h"
#include "imengine/RuntimeError.h"

#include "boost/math/special_functions.hpp"

#include "gsl/gsl_errno.h"
#include "gsl/gsl_roots.h"
#include "gsl/gsl_sf_gamma.h"

#include <cmath>

namespace local = imengine::models;

local::SersicDemo::SersicDemo(double re, double index, double e1, double e2, double rmax)
: _initialized(false), _twopi(8*std::atan(1.0)), _transform(e1,e2)
{
    _transform.setObserver(getObserver());
    setParameters(re, index, e1, e2, rmax);
}

local::SersicDemo::~SersicDemo() { }

void local::SersicDemo::setParameters(double re, double index,
double e1, double e2, double rmax) {
    _transform.setParameters(e1,e2);
    if(_initialized && re == _re && index == _index && rmax == _rmax) return;
    assertGreaterThan<double>("SersicDemo re",re,0);
    assertGreaterThanOrEqualTo<double>("SersicDemo rmax",rmax,0);
    // Minimum index is set by the numerical stability of kValue()
    assertGreaterThan<double>("SersicDemo index",index,0.2);
    _re = re;
    _rmax = rmax;
    if(!_initialized || _index != index) {
        _index = index;
        _inverseIndex = 1/_index;
        _alphaScale = std::pow(kValue(_index),-_index);
    }
    _alpha = _re*_alphaScale;
    _norm = _twopi*_alpha*_alpha*_index*
        boost::math::tgamma(2*_index)/_transform.determinant();
    _initialized = true;
    setChanged();
}

double local::SersicDemo::operator()(double x, double y) const {
    double r(_transform.transformedRadius(x,y));
    if(_rmax > 0 && r > _rmax) return 0;
    return std::exp(-std::pow(r/_alpha,_inverseIndex))/_norm;
}

double local::SersicDemo::kValueF(double x, void *params) {
    double *dparams = static_cast<double*>(params);
    double result = gsl_sf_gamma_inc(dparams[0],x) - dparams[1];
    //std::cout << "F(" << x << ") = " << result << std::endl;
    return result;
}

double local::SersicDemo::kValueDF(double x, void *params) {
    double *dparams = static_cast<double*>(params);
    double result = -std::exp(-x)*std::pow(x,dparams[0]-1);
    //std::cout << "dF(" << x << ") = " << result << std::endl;
    return result;
}

void local::SersicDemo::kValueFDF(double x, void *params, double *y, double *dy) {
    double *dparams = static_cast<double*>(params);
    double two_n(dparams[0]);
    *y = gsl_sf_gamma_inc(two_n,x) - dparams[1];
    *dy = -std::exp(-x)*std::pow(x,two_n-1);
    //std::cout << "X = " << x << ", F(X) = " << *y << ", dF(X) = " << *dy << std::endl;
}

double local::SersicDemo::kValue(double index) {
    // Use the asymmptotic result for large index (which would otherwise overflow
    // when evaluating the Gamma function)
    if(index > 25) return 2*index - 1./3.;
    const gsl_root_fdfsolver_type *T(gsl_root_fdfsolver_steffenson);
    gsl_root_fdfsolver *s(gsl_root_fdfsolver_alloc(T));
    if(0 == s) throw RuntimeError("SersicDemo::kValue: alloc failed.");
    gsl_function_fdf FDF;
    FDF.f = SersicDemo::kValueF;
    FDF.df = SersicDemo::kValueDF;
    FDF.fdf = SersicDemo::kValueFDF;
    double dparams[2] = { 2*index, 0.5*gsl_sf_gamma(2*index) };
    FDF.params = &dparams;
    double x0,x(2*index);
    gsl_root_fdfsolver_set(s, &FDF, x);
    int status,iter(0);
    do {
        // do one iteration of improving the root
        iter++;
        status = gsl_root_fdfsolver_iterate(s);
        // remember our initial guess for this iteration
        x0 = x;
        // lookup the improved estimate after this iteration
        x = gsl_root_fdfsolver_root(s);
        // test for |x - x0| < 1e-8 + 1e-6*x
        status = gsl_root_test_delta(x, x0, 1e-8, 1e-6);
        if (status == GSL_SUCCESS) break;
        //std::cout << iter << ' ' << x << ' ' << x0 << std::endl;
    } while(status == GSL_CONTINUE);
    gsl_root_fdfsolver_free (s);
    return x;
}
#ifndef MYBEZIER_H
#define MYBEZIER_H

#include "parametrics/gmpcurve.h"

//#include <gmParametricsModule>

#include "mycircle.h"

namespace HXlib {

template <typename T>
class MyBezier : public GMlib::PCurve<T,3>
{
    GM_SCENEOBJECT(MyBezier)
public:
    MyBezier(GMlib::PCurve<T,3>* originalCurve, T startP, T centerP, T endP, int degreeDerivatives);
    //MyBezier(GMlib::DVector point_);


protected:
    void        eval(T t, int d, bool l);
    T           getEndP();
    T           getStartP();
    bool        isClosed() const;

    void MatrixEval(GMlib::DMatrix<T> &evalMat, int degree, T scaler, T centerP);
    void localSimulate(double dt);
    T derivativesScaling_;
    T scalingCenter_;
    int deg;

    GMlib::PCurve<T,3>* _c;
    //GMlib::PCurve<T,3>* _p;
    GMlib::DVector<GMlib::Vector<T,3>> controllPoints_;

};


} // END namepace HXlib

#include "mybezier.c"

#endif // MYBEZIER_H


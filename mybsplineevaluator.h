
#ifndef MYBSPLINEEVALUATOR_H
#define MYBSPLINEEVALUATOR_H

#include <gmCoreModule>
#include "knotvector.h"
#include <core/containers/gmdvector.h>

#include <gmParametricsModule>


#include "parametrics/gmpcurve.h"


namespace HXlib {


template <typename T>
class MyBsplineEvaluator : public GMlib::DMatrix<T>
{
public:
    MyBsplineEvaluator();

    void bSplineEval(GMlib::DMatrix<T> &myMatrix, const std::shared_ptr<HXlib::KnotVector<T>> knotVec, int degree, T tP);
    std::shared_ptr<HXlib::KnotVector<T>> knotVec_;

private:

    T getW(T tP, int degree, int index);
    T getDerivateW(T tP, int degree, int index);
    T delta(T scaler, int degree, int i);
    int findIndex(T tP, int i);

};



} // END namepace HXlib


#include "mybsplineevaluator.c"



#endif // MYBSPINEEVALUATOR_H



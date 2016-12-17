#ifndef MYERBS_H

#define MYERBS_H
#include "knotvector.h"
#include "mycircle.h"
#include "mysubcurve.h"


#include "mybezier.h"

#include <gmParametricsModule>
#include <parametrics/gmpcylinder>




namespace HXlib {

template <typename T>
class MyERBS : public GMlib::PCurve<T,3>
{
    GM_SCENEOBJECT(MyERBS)
    public:

    MyERBS(MyCircle<T>* curve, int numLC);

    void createSubCurve();
    void createBezierCurve();

    void subCurveInEval(T t, int d);
    void bezierCurveInEval(T t, int d);

//    T calculateBFB1(T tP);


//    T calculateBFBDer1(T tP, T scale);
//    T calculateBFBDer2(T tP, T scale);
    GMlib::DVector<float> B(T tP,int d, T scale);


protected:
    void	        eval(T t, int d, bool l);

    T               getEndP();
    T               getStartP();

    void localSimulate(double dt);
private:
    bool ready_ = false;
    double sum_ = 0;

    GMlib::DMatrix<T> matrix_;
    //std::shared_ptr<HXlib::KnotVector<T>> myknotvector_;
    GMlib::DVector<T>  myknotvector_;
    MyCircle<T>* mycircle_;
    std::vector<std::shared_ptr<HXlib::MySubCurve<T>>> currentSubCurve_;
    std::vector<std::shared_ptr<HXlib::MyBezier<T>>> currentBezierCurve_;



};







}   // END namepace HXlib

#include "myerbs.c"

#endif // MYERBS_H

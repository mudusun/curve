#ifndef KNOTVECTOR_H
#define KNOTVECTOR_H



#include <vector>
#include <core/containers/gmdvector.h>
#include "mycircle.h"
#include <memory>

namespace HXlib {
template <typename T>
class KnotVector : GMlib::DVector<T>
{

public:
    KnotVector( MyCircle<T>* circle, float numLC);
    GMlib::DVector<T> getKnotVector();

   //int getSize();
   //T getParameters(int i);
private:

    T endParameter_;
    GMlib::DVector<T> knotVec_;


    float endP_;
    float startP_;
    float step_;
    float start_;
    float current_;
    float center_;
    float end_;
    MyCircle<T>* mycurve_;

};


} // END namespace HXlib
#include "knotvector.c"
#endif // KNOTVECTOR_H


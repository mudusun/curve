#include "knotvector.h"

namespace HXlib {


template <typename T>
inline
KnotVector<T>::KnotVector( MyCircle<T>* mycurve, float numLC) // numLC:number of local curve
{
    mycurve_ = mycurve;
    knotVec_.setDim(numLC +3);// DVector must have dimension

    startP_ = mycurve_->getParStart();
    endP_ = mycurve_->getParEnd();

    step_ = (endP_ - startP_)/ (numLC-0); // Num of intervals. Ett mindre intervall enn knots (bestandig)
    start_ = startP_ - step_;
    current_ = startP_ - step_;
    center_ = startP_;
    endParameter_ = endP_ + step_;



    // If he/she is OPEN then set the two last/first knots equal
    if(!mycurve_->isClosed())
    {
        for(int i = 0; i < 2; i++)
        {
            knotVec_[i] = startP_;
            knotVec_[numLC+1] = endP_;
        }
    }
    int k = 0;
    if(mycurve_->isClosed())
        k = 2;
    else
        k = 1;

    // Take in the tP's (Closed)
    for(int i = 1; i < numLC+k; i++)
    {
        //(*this)[i] = step_*(i-1);
        knotVec_[i] = start_ + step_*(i);
    }
    // check han/hun er closed
    if(mycurve_->isClosed())
    {
        knotVec_[0] = start_;
        knotVec_[numLC+2] = endParameter_;
    }
    // print out knotVector
    for(int i = 0; i < numLC +2; i++)
    {
        //std::cout<<"THis "<<(*this)[i]<<std::endl;
    }
}

/*template <typename T>
int KnotVector<T>::getSize()
{
    return knotVec_.getDim();
}

template <typename T>
//T KnotVector<T>::getParameters(int i)*/
//{
// return knotVec_[i];
//}

template <typename T>
GMlib::DVector<T> KnotVector<T>::getKnotVector()
{
 return knotVec_;
}


} // END namespace HXlib

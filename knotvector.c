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

    step_ = (endP_ - startP_)/ (numLC); // Num of intervals. One interval less than knots (constant)
    start_ = startP_ - step_;
    current_ = startP_ - step_;
    center_ = startP_;
    endParameter_ = endP_ + step_;



    // If it is OPEN then set the two last/first knots equal
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
    // check if it is closed
    if(mycurve_->isClosed())
    {
        knotVec_[0] = start_;
        knotVec_[numLC+2] = endParameter_;
    }

    // Take in the tP's (Closed)
    for(int i = 1; i < numLC+k; i++)
    {
        knotVec_[i] = start_ + step_*(i);
    }

    // print out knotVector
    for(int i = 0; i < numLC +2; i++)
    {
        //std::cout<<"knotVector "<<(*this)[i]<<std::endl;
    }
}



template <typename T>
GMlib::DVector<T> KnotVector<T>::getKnotVector()
{
 return knotVec_;
}


} // END namespace HXlib

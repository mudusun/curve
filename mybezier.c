#include "mybezier.h"
namespace HXlib {

template <typename T>
MyBezier<T>::MyBezier(GMlib::PCurve<T,3>* originalCurve, T startP, T centerP, T endP, int degreeDerivatives)
{
    deg = degreeDerivatives;
    GMlib::DVector<GMlib::Vector<T,3>> evaluateCurve = originalCurve->evaluateParent(centerP, degreeDerivatives);
    scalingCenter_ = (centerP-startP)/(endP-startP); // (t[i] - t[i-1]) / (t[i+1] - t[i-1]) equation 7.32 P195
    derivativesScaling_ = 1 / (endP-startP); //    1 / (t[i+1]- t[i-1]) equation 8.11.

    // See mycircle where we set dim to +1 and now we need to take -1 to get the original d
    GMlib::DMatrix<T> evalMat;

    MatrixEval(evalMat, deg,derivativesScaling_,scalingCenter_);

    //std::cout <<"eval matrix"<< evalMat_ << std::endl;

    controllPoints_ = evalMat.invert() * evaluateCurve; // equation 8.13  coefficients p. 226  evalMat是P88的 公式中间的大矩阵。 c0,c1,c2...是control point。

    for(int i = 0; i < evaluateCurve.getDim(); i++)
    {
        controllPoints_[i] -= evaluateCurve[0];
    }

    // std::cout <<"p"<< controllPoints_ << std::endl;
    _c = originalCurve;
    this->translateParent(evaluateCurve[0]);

}

//template <typename T>
//MyBezier<T>::MyBezier(GMlib::DVector point_)
//{
//    controllPoints_ = point_;
//}

template <typename T>
void MyBezier<T>::MatrixEval(GMlib::DMatrix<T> &evalMat_, int degree, T scaler, T tP)
{

    if (degree < 1)
    {
        evalMat_.setDim (1 , 1) ;
        evalMat_[0][0] = 1 ;
        return ; // Initiate the result matrix Escape in the case of degree zero
    }
    else
        evalMat_.setDim(degree +1 ,degree+1);

    // Compute all Bernstein polynomials up to degree d.   P93
    // Each degree at each row, starting from the bottom up.
    evalMat_[degree-1][0] = 1 - tP;
    evalMat_[degree-1][1] = tP;                                                             // The general Cox/deBoor like algorithm for

    for (int i = degree-2; i >= 0 ; i-- )                                                   //- Bezier/Bernstein computing the triangle
    {
        evalMat_[i][0] = (1 - tP) * evalMat_[i + 1][0];                                     // -of all values from "Bernstein" polynomial

        for(int j = 1; j < degree - i ; j ++ )                                              // - of degree 1 to d, respectively in each row.
        {
            evalMat_[i][j] = tP * evalMat_[i + 1][j -1] + (1 - tP) *evalMat_[i + 1][j] ;
        }

        evalMat_[i][degree-i] = tP * evalMat_ [i + 1][degree-i-1];
    }
 //       degree = 3  公式4.30
 //             ----------|---------------|------------|------
 //             (1-t)pow3 |  3t(1-t)pow2  | 3pow2(1-t) |  tpow3
 //             (1-t)pow2 |   2t(1-t)     |  tpow2     |
 //             (1-t)     |   t           |            |
 //


    for (int n = 0; n<evalMat_ .getDim2();n++)
    {
       // std::cout<<"evalmat: "<< evalMat_[0][n] <<std::endl;
    }

// Compute all the derivatives that exist
    evalMat_ [degree][0] = -scaler ;
    evalMat_ [degree][1] = scaler ;                                         // Multiply all rows except the upper one

    for( int k = 2 ; k <= degree; k++ )                                     //- with the derivative matrices in the
    {
        const double s = k * scaler ;                                       // - expression (8.10), and the scalings

        for (int i = degree ; i > degree - k ; i-- )                        // - so every row extends the number
        {
            evalMat_[i][k] = s * evalMat_ [i][k -1];                        // - of elements to d.

            for(int j = k - 1 ; j > 0 ; j-- )
            {
               evalMat_[i][j] = s * (evalMat_ [i][j -1] - evalMat_ [i][j]);
            }

            evalMat_[i][0] = -s * evalMat_[i][0];
        }
    }

    //       degree = 3  公式
    //                   0            1              2          3
    //             ----------|---------------|------------ |----------
    //         0    (1-t)pow3 |  3t(1-t)pow2  | 3pow2(1-t) |  tpow3
    //         1    (1-t)pow2 |   2t(1-t)     |  tpow2     |  k * scaler * evalMat_ [3][1]
    //         2    (1-t)     |   t           |  2scaler_t |
    //         3       -scaler|       scaler  |2pow_scaler |


}

template <typename T>
void MyBezier<T>::eval(T t, int d, bool /*l*/)

{   //this->_p.setDim(deg+1);
    GMlib::DMatrix<T> evalMat;
    MatrixEval(evalMat,controllPoints_.getDim()-1,derivativesScaling_,t);
    // this->_p     =  _c->evaluateParent(t , d);
     this->_p = evalMat*controllPoints_;
  //  std::cout <<"p"<< evalMat*controllPoints_ << std::endl;

}

template <typename T>
T MyBezier<T>::getEndP()
{
    return T(1);
}

template <typename T>
T MyBezier<T>::getStartP()
{
    return T(0);
}

template <typename T>
bool MyBezier<T>::isClosed() const
{
    return false;
}

template <typename T>
void MyBezier<T>::localSimulate(double dt)
{
//    this->translate(GMlib::Vector<T,3>(0.2,0.0,0.0));
    this->rotate(GMlib::Angle(10* dt), GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));

}

} // END namespace XHlib



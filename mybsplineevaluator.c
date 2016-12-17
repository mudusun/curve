#include "mybsplineevaluator.h"




namespace HXlib {


template <typename T>
MyBsplineEvaluator<T>::MyBsplineEvaluator()
{

}


template <typename T>
T MyBsplineEvaluator<T>::getW(T tP, int degree, int index)
{
    return (tP-knotVec_->getParameters(index))/(knotVec_->getParameters(index+degree)-knotVec_->getParameters(index));
}

template <typename T>
T MyBsplineEvaluator<T>::getDerivateW(T tP, int degree, int index)
{
    return T(1)/ (knotVec_->getParameters(index+degree) - knotVec_->getParameters(index));
}

template <typename T>
void MyBsplineEvaluator<T>::MatrixEval(T tP, int degree)
{

    int index = degree;
    if(tP > myknotvector_->getParameters(index+1))
    {
        index++;
    }

    matrix_.setDim(degree+1,degree+1);
    // Transformed t value
    GMlib::DVector<T> w(degree);

    T scale = (tP-myknotvector_->getParameters(index))/(myknotvector_->getParameters(index+degree)-myknotvector_->getParameters(index));

    // Compute the Bernstein polynomials 1 ->d.
    // One for each row, starting from the bottom up.
    matrix_[degree - 1][0] = 1 - scale;
    matrix_[degree - 1][1] = scale;

    for(int i = degree-2, d_c = 2; i >= 0; i--, d_c++)
    {
       // Generate w
       w.setDim(d_c);
       for(int j = d_c; j > 0; j--)
       {
           w[j-1] = getW(tP, d_c,index - (d_c - j));
       }
       // Compute the Bernstein polynomials
       matrix_[i][0] = (1- w[0]) * matrix_[i+1][0];

       for(int k = 1; k < degree-i; k++)
       {
           matrix_[i][k] = w[k-1]* matrix_[i+1][k-1] + (1- w[k]) * matrix_[i+1][k];
       }
       matrix_[i][degree-i] = w[d_c-1]* matrix_[i+1][degree-i-1];
    }
    // Compute all the derivatives
    matrix_[degree][0] = -getDerivateW(tP,1,index);
    matrix_[degree][1] = getDerivateW(tP,1,index);

    for(int i = 2; i <= degree; i++)
    {
        for(int j = degree, d_c = 2; j > degree-i; j--, d_c++)
        {

            // Generate w for the derivatives
            w.setDim(d_c);
            for(int k = 1; k <= d_c; k++)
            {
                w[k-1] = k* getDerivateW(tP,d_c,index -(d_c - k));
            }
            // Complete the Bernstein polynomials by adding the computation of derivatives
            matrix_[j][i] = w[0] * matrix_[j][i-1];

            for(int l = i-1, index_c = 1; l > 0; l--,index_c++)
            {
                matrix_[j][l] = w[index_c] * (matrix_[j][l-1] - matrix_[j][l]);
            }
            matrix_[j][0] = -w[d_c-1] * matrix_[j][0];
        }
    }

}


} // END namespace XHlib



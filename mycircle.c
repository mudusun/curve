#include "mycircle.h"




namespace HXlib {


  template <typename T>
  inline
  MyCircle<T>::MyCircle( T radius )
  {

    _r = radius;
    this->_dm = GMlib::GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  MyCircle<T>::~MyCircle() {}


  template <typename T>
  inline
  void MyCircle<T>::eval( T t, int d, bool /*l*/ )
  {

    this->_p.setDim( d + 1 );

    const T ct = _r * 2*cos(3*t/2)*cos(t);  //formula for the curve
    const T st = _r * 2*cos(3*t/2)*sin(t);

    this->_p[0][0] = ct;
    this->_p[0][1] = st;
    this->_p[0][2] = T(0);

    if( this->_dm == GMlib::GM_DERIVATION_EXPLICIT )
    {

      if( d > 0 )  // First derivative
      {

        this->_p[1][0] = -(1/2)*_r*(sin(t/2)+5*sin(5*t/2));
        this->_p[1][1] = -(1/2)*_r*(cos(t/2)-5*cos(5*t/2));
        this->_p[1][2] =  T(0);
      }

      if( d > 1 )
      {

        this->_p[2][0] = -(1/4)*_r *(cos(t/2) + 25 *cos((5* t)/2));
        this->_p[2][1] = 1/4* _r *(sin(t/2) - 25* sin((5* t)/2));
        this->_p[2][2] =  T(0);
      }

      if( d > 2 )
      {

        this->_p[3][0] =  1/8 * _r* (sin(t/2) + 125 *sin((5* t)/2));
        this->_p[3][1] =  1/8* _r* (cos(t/2) - 125 *cos((5* t)/2));
        this->_p[3][2] =  T(0);
      }

      if( d > 3 )
      {

        this->_p[4][0] =  1/16 * _r* (cos(t/2) + 625 *cos((5* t)/2));
        this->_p[4][1] = -1/16 * _r* (sin(t/2) - 625 *sin((5* t)/2));
        this->_p[4][2] =  T(0);
      }

      if( d > 4 )
      {

        this->_p[5][0] = -1/32* _r* (sin(t/2) + 3125 *sin((5* t)/2));
        this->_p[5][1] = -1/32* _r* (cos(t/2) - 3125 *cos((5* t)/2));
        this->_p[5][2] =  T(0);
      }



   }
  }


  template <typename T>
  inline
  T MyCircle<T>::getEndP()
  {

    return T( M_2PI );
  }


  template <typename T>
  inline
  T MyCircle<T>::getStartP()
  {

    return T(-M_2PI);
  }


  template <typename T>
  inline
  T MyCircle<T>::getRadius()
  {

    return _r;
  }


  template <typename T>
  inline
  bool MyCircle<T>::isClosed() const
  {

    return true;
  }


  template <typename T>
  inline
  void MyCircle<T>::setRadius( T radius )
  {

      _r = radius;
  }


} // END namespace XHlib



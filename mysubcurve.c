#include "mysubcurve.h"

namespace HXlib {


  // Constructors and destructors
  //******************************

  template <typename T>
  inline
  MySubCurve<T>::MySubCurve(MyCircle<T>* c, T s, T e )
  {
    this->_dm = GMlib::GM_DERIVATION_EXPLICIT;

    set(c, s, e, (e+s)/2);

    GMlib::DVector<GMlib::Vector<T,3> > tr = _c->evaluateParent(_t, 0);
    _trans = tr[0];
    this->translateParent( _trans );
  }


  template <typename T>
  inline
 MySubCurve<T>::MySubCurve( MyCircle<T>* c, T s, T e, T t )
  {
    this->_dm = GMlib::GM_DERIVATION_EXPLICIT;

    set(c, s, e, t);

    GMlib::DVector<GMlib::Vector<T,3> > tr = _c->evaluateParent(_t, 0);
    _trans = tr[0];
    this->translateParent( _trans );
  }


  template <typename T>
  inline
  MySubCurve<T>::MySubCurve( const MySubCurve<T>& copy ) :MyCircle<T>( copy )
  {
    set(copy._c, copy._s, copy._e, copy._t);

    _trans = copy._trans;
  }


  template <typename T>
   MySubCurve<T>::~ MySubCurve() {}


  // Virtual functions from PSurf
  //******************************

  template <typename T>
 /*************/ void MySubCurve<T>::eval( T t, int d, bool /*l*/ )
  {
    this->_p     = _c->evaluateParent(t , d);
    this->_p[0] -= _trans;
  }


  template <typename T>
  T MySubCurve<T>::getStartP()
  {
    return _s;
  }


  template <typename T>
  T MySubCurve<T>::getEndP()
  {
    return _e;
  }


  template <typename T>
  bool MySubCurve<T>::isClosed() const
  {
    return false;
  }


  // Private help functions
  //*************************

  template <typename T>
  inline
  void MySubCurve<T>::set (MyCircle<T>* c, T s, T e, T t)
  {
    _c = c;
    _s = s;
    _t = t;
    _e = e;
  }

template <typename T>
  void MySubCurve<T>::localSimulate(double dt)
  {
     this->rotate(GMlib::Angle(M_PI/4 * dt), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ));

  }


} // END namespace HXlib


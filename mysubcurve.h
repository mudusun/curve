
#ifndef MYSUBCURVE_H
#define MYSUBCURVE_H


#include "parametrics/gmpcurve.h"

#include "mycircle.h"

namespace HXlib {


  template <typename T>
  class MySubCurve : public MyCircle<T>
  {
    GM_SCENEOBJECT(MySubCurve)
  public:
    MySubCurve( MyCircle<T>* c, T s, T e);
    MySubCurve( MyCircle<T>* c, T s, T e, T t);
    MySubCurve( const MySubCurve<T>& copy );

    virtual ~MySubCurve();

    // virtual functions from PSurf
    virtual bool            isClosed() const;
    // Local functions
    void                    togglePlot();

  protected:

    MyCircle<T>*        _c;
    T                   _s;
    T                   _t;
    T                   _e;
    GMlib::Vector<float,3>     _trans;

    // virtual functions from PSurf
    void                eval( T t, int d, bool l = false );
    T                   getEndP();
    T                   getStartP();

  private:

    // Local help functions
    void set(MyCircle<T>* c, T s, T e, T t);
    void localSimulate(double dt);

  }; // END class MySubCurve

} // END namepace HXlib


// Include MySubCurve class function implementations

#include "mysubcurve.c"


#endif // MYSUBCURVE_H



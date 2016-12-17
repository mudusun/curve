#ifndef MYCURVE_H
#define MYCURVE_H


#include "parametrics/gmpcurve.h"


namespace HXlib {


  template <typename T>
  class MyCircle : public GMlib::PCurve<T,3>
  {
    GM_SCENEOBJECT(MyCircle)
  public:
    MyCircle( T radius = T(3) );
    //MyCircle( const MyCircle<T>& copy );
    virtual ~MyCircle();

    T               getRadius();
    bool            isClosed() const;
    void            setRadius( T radius = T(3) );


  protected:
    T               _r;

    void	          eval(T t, int d, bool l);
    T               getEndP();
    T               getStartP();

  }; // END class MyCircle

} // END namepace HXlib

// Include myCircle class function implementations
#include "mycircle.c"


#endif // MYCIRCLE_H

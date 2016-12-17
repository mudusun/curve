#ifndef SCENARIO_H
#define SCENARIO_H


#include "application/gmlibwrapper.h"

// qt
#include <QObject>

namespace HXlib {
template <typename T>
class MyERBS;
}



class Scenario : public GMlibWrapper
{
  Q_OBJECT
public:
  using GMlibWrapper::GMlibWrapper;

  void    initializeScenario() override;
  void    cleanupScenario() override;
  void    testingReplot();

private:

  std::shared_ptr<HXlib::MyERBS<float>> myerbs_;


};
#endif // SCENARIO_H

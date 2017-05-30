
#pragma once

#ifdef MOCK_TEST
#include "ev3mock.h"
namespace ev3 = ev3mock;
#warning compiling for mocked test
#else
#include "ev3dev.h"
namespace ev3 = ev3dev;
#endif

#include <string>
#include <map>

class sensorcontrol
{
protected:
  sensorcontrol() {}
public:
  ~sensorcontrol() {};

  virtual void connect(std::function<void(int)> f, std::string const & n) { _listeners[n] = f; }
  virtual void disconnect(std::string const & n) { _listeners[n] = nullptr; }

protected:
  std::map<std::string, std::function<void(int)> > _listeners;

};


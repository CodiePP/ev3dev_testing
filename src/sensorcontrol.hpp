
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
  virtual ~sensorcontrol() {};

  // add a listener function
  virtual void connect(std::function<void(int)> f, std::string const & n) { _listeners[n] = f; }
  // remove a listener
  virtual void disconnect(std::string const & n) { _listeners[n] = nullptr; }
  // run the sensor
  virtual void run() = 0;
  // stop the sensor
  virtual void stop() = 0;

protected:
  std::map<std::string, std::function<void(int)> > _listeners;

};


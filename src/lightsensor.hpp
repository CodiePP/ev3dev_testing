
#pragma once

#ifdef MOCK_TEST
#include "ev3mock.h"
namespace ev3 = ev3mock;
#warning compiling for mocked test
#else
#include "ev3dev.h"
namespace ev3 = ev3dev;
#endif

#include "sensorcontrol.hpp"

#include <memory>
#include <thread>


class lightsensor : public sensorcontrol
{
public:
  lightsensor(ev3::address_type a);
  virtual ~lightsensor();

  virtual void run() override;
  virtual void stop() override;
#ifdef MOCK_TEST
  ev3::sensor* get_sensor() { return _sensor.get(); }
#endif

private:
  bool _running { false };
  bool _stopping { false };
  std::unique_ptr<ev3::color_sensor> _sensor;
  std::thread *_thr;
};


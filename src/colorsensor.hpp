
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


class colorsensor : public sensorcontrol
{
public:
  colorsensor(ev3::address_type a);
  ~colorsensor() {};

  //virtual void connect(std::function<void(int)>, std::string const &) override;
  //virtual void disconnect(std::string const &) override;

};


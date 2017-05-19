
#pragma once

#ifdef MOCK_TEST
#include "ev3mock.h"
namespace ev3 = ev3mock;
#warning compiling drivecontrol for mocked test
#else
#include "ev3dev.h"
namespace ev3 = ev3dev;
#endif

class drivecontrol
{
public:
  drivecontrol(ev3::large_motor * left, ev3::large_motor * right)
    : _motor_left(left), _motor_right(right) {}
  ~drivecontrol() {};

  void drive(int speed, int time=0);
  void turn(int direction);
  void stop();

protected:
  ev3::large_motor    * _motor_left {nullptr};
  ev3::large_motor    * _motor_right {nullptr};

  enum state
  {
    state_idle,
    state_driving,
    state_turning
  };

  state _state;
};


#include "drivecontrol.hpp"

#include <thread>
#include <chrono>
#include <iostream>


void drivecontrol::wait()
{
    while (_motor_left->state().count("running")
        || _motor_right->state().count("running")) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void drivecontrol::drive(int speed, int time)
{
  _motor_left->set_speed_sp(speed);
  _motor_right->set_speed_sp(speed);

  _state = state_driving;

  if (time > 0)
  {
    _motor_left->set_time_sp(time).run_timed();
    _motor_right->set_time_sp(time).run_timed();

    wait();

    _state = state_idle;
  }
  else
  {
    _motor_left->run_forever();
    _motor_right->run_forever();
  }

}

void drivecontrol::turn(int direction)
{
  if (_state != state_idle)
    stop();

  if (direction == 0)
    return;

  _state = state_turning;

  _motor_left->set_position_sp( direction).set_speed_sp(300).run_to_rel_pos();
  _motor_right->set_position_sp(-direction).set_speed_sp(300).run_to_rel_pos();

  wait();

  _state = state_idle;
}

void drivecontrol::stop()
{
  _motor_left->stop();
  _motor_right->stop();

  _state = state_idle;
}



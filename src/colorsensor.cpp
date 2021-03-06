
#include "colorsensor.hpp"

#include <iostream>
#include <thread>
#include <chrono>


#define THREAD_SLEEP_TIME 200

colorsensor::colorsensor(ev3::address_type a)
{
  _sensor.reset(new ev3::color_sensor(a));
}

colorsensor::~colorsensor()
{
  if (_running) {
    _stopping = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(2 * THREAD_SLEEP_TIME));
  }
}

void colorsensor::run()
{
  if (_running) {
    throw "already running!";
    return;
  }
  _running = true;
  //std::clog << "colorsensor::run()" << std::endl;

  // initialize first
  _sensor->color(true);

  _thr = new std::thread([&]()-> void {
      int _lastc = -1;
      while (! _stopping) {
          std::clog << "colorsensor::run()" << std::endl;
          std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_TIME));
          if (_stopping) { break; }

          int c = _sensor->color(false);
          if (c != _lastc) {
            std::clog << "    //  sensor returned " << c << "  \\\\" << std::endl;
            for (auto l : _listeners) {
                std::get<1>(l)(c); // report color
            }
            _lastc = c;
          }
      } // while
      _running = false;
      _stopping = false;
      std::clog << "colorsensor::run()  terminated!" << std::endl;
    });
}

void colorsensor::stop()
{
  _stopping = true;
  std::clog << "colorsensor::stop()" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(2*THREAD_SLEEP_TIME));
}


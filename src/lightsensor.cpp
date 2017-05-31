
#include "lightsensor.hpp"

#include <thread>
#include <chrono>


#define THREAD_SLEEP_TIME 200

lightsensor::lightsensor(ev3::address_type a)
{
  _sensor.reset(new ev3::color_sensor(a));
}

lightsensor::~lightsensor()
{
  if (_running) {
    _stopping = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(2 * THREAD_SLEEP_TIME));
  }
}

void lightsensor::run()
{
  if (_running) {
    throw "already running!";
    return;
  }
  _running = true;
  //std::clog << "lightsensor::run()" << std::endl;

  // initialize first
  _sensor->reflected_light_intensity(true);

  _thr = new std::thread([&]()-> void {
      int _lastc = -1;
      while (! _stopping) {
          std::clog << "lightsensor::run()" << std::endl;
          std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_TIME));
          if (_stopping) { break; }

          int c = _sensor->reflected_light_intensity(false);
          if (c != _lastc) {
            std::clog << "    //  sensor returned " << c << "  \\\\" << std::endl;
            for (auto l : _listeners) {
                std::get<1>(l)(c); // report light
            }
            _lastc = c;
          }
      } // while
      std::clog << "lightsensor::run()  terminated!" << std::endl;
      _running = false;
      _stopping = false;
    });
}

void lightsensor::stop()
{
  _stopping = true;
  std::clog << "lightsensor::stop()" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(2*THREAD_SLEEP_TIME));
}


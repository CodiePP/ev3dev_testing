
// select target platform
#define EV3DEV_PLATFORM_EV3
#include "ev3dev.h"

namespace ev3 = ev3dev;
#include "colorsensor.hpp"

#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char **argv)
{
  ev3::led led(ev3::led::red_left);
  colorsensor csnsr(ev3::INPUT_1);

  led.off();
  csnsr.connect([&led](int _c) -> void {
      if (_c == 5) { led.on(); }
      else { led.off(); }
    }, "follow_color");
  csnsr.run();

  for (int i = 0; i < 20; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  csnsr.stop();

  return 0;
}


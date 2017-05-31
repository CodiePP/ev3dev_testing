
// select target platform
#define EV3DEV_PLATFORM_EV3
#include "ev3dev.h"

#include <iostream>
#include <chrono>
#include <thread>

namespace ev3 = ev3dev;


void wait_for_button(ev3::button &btn)
{
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    if (btn.pressed()) { break; }
  } // while
}

int main(int argc, char **argv)
{
  ev3::button btn_enter(ev3::button::enter);
  ev3::button btn_up(ev3::button::up);

  std::clog << "press the UP button, please." << std::endl;
  wait_for_button(btn_up);

  std::clog << "press the ENTER button, please." << std::endl;
  wait_for_button(btn_enter);

  std::clog << "Thank you.    .. not bad!" << std::endl;
  return 0;
}


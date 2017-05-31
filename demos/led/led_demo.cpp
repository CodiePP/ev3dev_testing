
// select target platform
#define EV3DEV_PLATFORM_EV3
#include "ev3dev.h"

#include <chrono>
#include <thread>

namespace ev3 = ev3dev;


int main(int argc, char **argv)
{
  ev3::led led1(ev3::led::red_left);
  ev3::led led2(ev3::led::red_right);

  led1.off();
  led2.on();
  //led1.flash(200,200);
  //led2.flash(200,200);
  for (int i = 0; i < 20; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(333));
    if (led1.brightness() == 0) {
      led1.on(); led2.off(); }
    else {
      led1.off(); led2.on(); }
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  led1.off();
  led2.off();

  return 0;
}



// select target platform
#define EV3DEV_PLATFORM_EV3
#include "ev3dev.h"

namespace ev3 = ev3dev;
#include "drivecontrol.hpp"


int main(int argc, char **argv)
{
  ev3::large_motor mleft(ev3::OUTPUT_B);
  //mleft.set_polarity("inversed");
  ev3::large_motor mright(ev3::OUTPUT_C);
  //mright.set_polarity("inversed");

  drivecontrol drct(&mleft, &mright);

  // drive 10 cm forward
  drct.drive(-100, 2000);

  // turn 30 degrees
  drct.turn(30*3);

  // drive 3 cm backward
  drct.drive(100, 1000);

  // wait for completion
  drct.wait();

  // stop
  drct.stop();

  return 0;
}


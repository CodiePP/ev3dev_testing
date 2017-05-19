
// select target platform
#define EV3DEV_PLATFORM_EV3
#include "ev3dev.h"

namespace ev3 = ev3dev;
#include "drivecontrol.hpp"


int main(int argc, char **argv)
{
  ev3::large_motor mleft(ev3::OUTPUT_B);
  ev3::large_motor mright(ev3::OUTPUT_C);

  drivecontrol drct(&mleft, &mright);

  // drive 10 cm forward
  drct.drive(10*100);

  // turn 30 degrees
  drct.turn(30);

  // drive 3 cm backward
  drct.drive(-3*100);

  return 0;
}



#include <gtest/gtest.h>

// select target platform
#define EV3DEV_PLATFORM_EV3
#include "ev3mock.h"

namespace ev3 = ev3mock;
#include "drivecontrol.hpp"

namespace {

// test fixture
class MotorTest : public ::testing::Test {
  protected:
    MotorTest() {
      _ctrl.reset(new drivecontrol(&_mleft, &_mright));
    }
    virtual ~MotorTest() {}

    virtual void SetUp() {}
    virtual void TearDown() {}

    ev3::large_motor    _mleft{ev3::OUTPUT_B};
    ev3::large_motor    _mright{ev3::OUTPUT_C};

    std::unique_ptr<drivecontrol> _ctrl;
};

// define tests
TEST_F(MotorTest, StopMotor) {
  EXPECT_NO_THROW(_mleft.stop());
  EXPECT_NO_THROW(_mright.stop());
}

TEST_F(MotorTest, DriveAround) {
  // drive 10 cm forward
  _ctrl->drive(10*100);

  // turn 30 degrees
  _ctrl->turn(30);

  // drive 3 cm backward
  _ctrl->drive(-3*100);
}

} // namespace

// run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


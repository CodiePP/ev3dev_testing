
#include <gtest/gtest.h>
#include <ev3dev.h>

// select target platform
#define EV3DEV_PLATFORM_EV3

namespace ev3 = ev3dev;

namespace {

// test fixture
class MotorTest : public ::testing::Test {
  protected:
    MotorTest() {}
    virtual ~MotorTest() {}

    virtual void SetUp() {}
    virtual void TearDown() {}

    ev3::large_motor     _motor{ev3::OUTPUT_B};
};

// define tests
TEST_F(MotorTest, InitializeMotor) {
  // only if run on target platform
  //EXPECT_TRUE(_motor.connected());
  //EXPECT_NO_THROW(_motor.stop());

  // here no such device
  EXPECT_FALSE(_motor.connected());
  EXPECT_ANY_THROW(_motor.stop());
}


} // namespace

// run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



#include <gtest/gtest.h>

// select target platform
#define EV3DEV_PLATFORM_EV3
#include "ev3mock.h"

namespace ev3 = ev3mock;
#include "colorsensor.hpp"

namespace {

// test fixture
class ColorTest : public ::testing::Test {
  protected:
    ColorTest() {
      _sensor.reset(new colorsensor(ev3::INPUT_1));
    }
    virtual ~ColorTest() {}

    virtual void SetUp() {}
    virtual void TearDown() {}

    std::unique_ptr<colorsensor> _sensor;
};

// define tests
TEST_F(ColorTest, GetBlue) {
  int color = -1;
  auto fun = [&color](int c) -> void {
    color = c;
  };
  EXPECT_NO_THROW(_sensor->connect(fun, "get_blue"));
}

} // namespace

// run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


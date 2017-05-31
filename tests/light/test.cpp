
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::AtLeast;

// select target platform
#define EV3DEV_PLATFORM_EV3
#include "ev3mock.h"

namespace ev3 = ev3mock;
#include "lightsensor.hpp"

#include <chrono>
#include <thread>
#include <iostream>

namespace {

// test fixture
class LightTest : public ::testing::Test {
  protected:
    LightTest() {
      _sensor.reset(new lightsensor(ev3::INPUT_1));
    }
    virtual ~LightTest() {}

    virtual void SetUp() {}
    virtual void TearDown() {
      if (_sensor) { _sensor->stop(); }
    }

    std::unique_ptr<lightsensor> _sensor;
};

// define tests
TEST_F(LightTest, GetLight) {
  int intensity = -1;
  auto fun = [&intensity](int c) -> void {
    intensity = c;
  };
  EXPECT_NO_THROW(_sensor->connect(fun, "get_light"));
  EXPECT_CALL(*_sensor->get_sensor(), value(0))
      .WillRepeatedly(Return(142));
  EXPECT_NO_THROW(_sensor->run());
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  EXPECT_NO_THROW(_sensor->stop());

  std::clog << "intensity = " << intensity << std::endl;
}

} // namespace

// run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


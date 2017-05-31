
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::AtLeast;

// select target platform
#define EV3DEV_PLATFORM_EV3
#include "ev3mock.h"

namespace ev3 = ev3mock;
#include "colorsensor.hpp"

#include <chrono>
#include <thread>
#include <iostream>

namespace {

// test fixture
class ColorTest : public ::testing::Test {
  protected:
    ColorTest() {
      _sensor.reset(new colorsensor(ev3::INPUT_1));
    }
    virtual ~ColorTest() {}

    virtual void SetUp() {}
    virtual void TearDown() {
      if (_sensor) { _sensor->stop(); }
    }

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

TEST_F(ColorTest, MayNotStartTwice) {
  int color = -1;
  auto fun = [&color](int c) -> void {
    color = c;
  };
  EXPECT_NO_THROW(_sensor->connect(fun, "get_color"));
  EXPECT_NO_THROW(_sensor->run());
  EXPECT_ANY_THROW(_sensor->run());
  EXPECT_ANY_THROW(_sensor->run());
  EXPECT_NO_THROW(_sensor->stop());
  EXPECT_NO_THROW(_sensor->run());
  EXPECT_ANY_THROW(_sensor->run());
}

TEST_F(ColorTest, GetColor) {
  int color = -1;
  auto fun = [&color](int c) -> void {
    color = c;
  };
  EXPECT_NO_THROW(_sensor->connect(fun, "get_color"));
  EXPECT_CALL(*_sensor->get_sensor(), value(0))
      .Times(5)
      .WillRepeatedly(Return(1));
  EXPECT_NO_THROW(_sensor->run());
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  EXPECT_CALL(*_sensor->get_sensor(), value(0))
      .WillOnce(Return(3))
      .WillOnce(Return(4))
      .WillOnce(Return(5))
      .WillOnce(Return(6));
      //.WillOnce(Return(7))
      //.WillOnce(Return(8));
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  EXPECT_NO_THROW(_sensor->stop());

  std::clog << "color = " << color << std::endl;
}

} // namespace

// run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


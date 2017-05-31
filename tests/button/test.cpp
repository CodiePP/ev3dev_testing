
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::AtLeast;

// select target platform
#define EV3DEV_PLATFORM_EV3
#include "ev3mock.h"

namespace ev3 = ev3mock;

#include <chrono>
#include <thread>
#include <iostream>


namespace {

// test fixture
class ButtonTest : public ::testing::Test {
  protected:
    ButtonTest() {}
    virtual ~ButtonTest() {}

    virtual void SetUp() {}
    virtual void TearDown() {}

    void wait_for_button(ev3::button &btn)
    {
      while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if (btn.pressed()) {
          std::clog << " got it!" << std::endl;
          break; }
        else { std::clog << "?"; }
      } // while
    }

    ev3::button btn_enter{ev3::button::enter};
    ev3::button btn_up{ev3::button::up};
};

// define tests
TEST_F(ButtonTest, Wait4Button) {

  std::clog << "press the UP button, please." << std::endl;

  EXPECT_CALL(btn_enter, pressed())
    .WillRepeatedly(Return(true));
  EXPECT_CALL(btn_up, pressed())
    .WillOnce(Return(false))
    .WillOnce(Return(false))
    .WillOnce(Return(false))
    .WillOnce(Return(false))
    .WillOnce(Return(true));

  wait_for_button(btn_up);
}


} // namespace

// run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


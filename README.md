This is an attempt to apply test-driven development (TDD) to the programming
of the [LEGO Mindstorms ev3](https://www.lego.com/en-us/mindstorms/about-ev3) robot in *C++*.

For this we use the great works of
  * [ev3dev](http://www.ev3dev.org) which provide a superior Linux image to be run on the robot
  * Google's testing and mocking framework [googletest](https://github.com/google/googletest.git)



directory structure
===================

demos/       demo programs to be executed on ev3
tests/       test programs
src/         source code

this repository depends on the following:

 1. https://github.com/ddemidov/ev3dev-lang-cpp.git
 2. https://github.com/google/googletest.git



initial checkout
================

after cloning this repository
you should also initialize its dependencies:

  `git submodule update --init --recursive`


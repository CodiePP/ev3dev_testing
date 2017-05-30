
#pragma once

#include <gmock/gmock.h>
#include <ev3dev.h>

#include <set>
#include <string>

namespace ev3mock {

  using device_type = ev3dev::device_type;
  using mode_type = ev3dev::mode_type;
  using mode_set = ev3dev::mode_set;
  using address_type = ev3dev::address_type;

  constexpr const char* INPUT_1  = ev3dev::INPUT_1;
  constexpr const char* INPUT_2  = ev3dev::INPUT_2;
  constexpr const char* INPUT_3  = ev3dev::INPUT_3;
  constexpr const char* INPUT_4  = ev3dev::INPUT_4;

  constexpr const char* OUTPUT_A = ev3dev::OUTPUT_A;
  constexpr const char* OUTPUT_B = ev3dev::OUTPUT_B;
  constexpr const char* OUTPUT_C = ev3dev::OUTPUT_C;
  constexpr const char* OUTPUT_D = ev3dev::OUTPUT_D;


  class device {
    public:
      bool connect(const std::string &dir,
                   const std::string &pattern,
                   const std::map<std::string, std::set<std::string>> &match) noexcept
        {
          _dir=dir, _pat=pattern, _match=match,
          //_devidx += 1; _device_index = _devidx;
          _path = dir + pattern + "/";
        }

      bool connected() const { return !_path.empty(); }

      int  device_index() const { return _device_index; }

      //int         get_attr_int   (const std::string &name) const;
      MOCK_CONST_METHOD1(get_attr_int, int(const std::string&));
      //void        set_attr_int   (const std::string &name, int value);
      MOCK_METHOD2(set_attr_int, void(const std::string&,int));
      //std::string get_attr_string(const std::string &name) const;
      MOCK_CONST_METHOD1(get_attr_string, std::string(const std::string&));
      //void        set_attr_string(const std::string &name,
      //                            const std::string &value);
      MOCK_METHOD2(set_attr_string, void(const std::string&,const std::string&));

      //std::string get_attr_line  (const std::string &name) const;
      MOCK_CONST_METHOD1(get_attr_line, std::string(const std::string&));
      //mode_set    get_attr_set   (const std::string &name,
      //                            std::string *pCur = nullptr) const;
      MOCK_CONST_METHOD1(get_attr_set, mode_set(const std::string&));

      //std::string get_attr_from_set(const std::string &name) const;
      MOCK_CONST_METHOD1(get_attr_from_set, std::string(const std::string&));

    protected:
      std::string _dir;
      std::string _pat;
      std::map<std::string, std::set<std::string>> _match;
      std::string _path;
      mutable int _device_index = -1;
    private:
      //static int _devidx;
  };

  class sensor : protected device {
    public:
      sensor(address_type a) { device::connect("/sys/devices/lego-sensor/", "sensor", {{ "address", { a }} }); }
      MOCK_CONST_METHOD1(value, int(int));
      MOCK_CONST_METHOD1(float_value, float(int));
      MOCK_CONST_METHOD0(type_name, std::string());

      std::string address() const { return get_attr_string("address"); }
      auto set_mode(std::string m) -> decltype(*this) {
        set_attr_string("mode", m); return *this; }
      std::string mode() const { return get_attr_string("mode"); }
  };


  class color_sensor : public sensor {
    public:
      color_sensor(address_type a) : sensor(a) {}

      int reflected_light_intensity(bool do_set_mode = true) {
        if (do_set_mode) set_mode(ev3dev::color_sensor::mode_col_reflect);
        return value(0);
      }

      int ambient_light_intensity(bool do_set_mode = true) {
        if (do_set_mode) set_mode(ev3dev::color_sensor::mode_col_ambient);
        return value(0);
      }
      // Color detected by the sensor, categorized by overall value.
      //   - 0: No color
      //   - 1: Black
      //   - 2: Blue
      //   - 3: Green
      //   - 4: Yellow
      //   - 5: Red
      //   - 6: White
      //   - 7: Brown
      int color(bool do_set_mode = true) {
        if (do_set_mode) set_mode(ev3dev::color_sensor::mode_col_color);
        return value(0);
      }

      // Red, green, and blue components of the detected color, in the range 0-1020.
      std::tuple<int, int, int> raw(bool do_set_mode = true) {
        if (do_set_mode) set_mode(ev3dev::color_sensor::mode_rgb_raw);
        return std::make_tuple( value(0), value(1), value(2) );
      }

      // Red component of the detected color, in the range 0-1020.
      int red(bool do_set_mode = true) {
        if (do_set_mode) set_mode(ev3dev::color_sensor::mode_rgb_raw);
        return value(0);
      }

      // Green component of the detected color, in the range 0-1020.
      int green(bool do_set_mode = true) {
        if (do_set_mode) set_mode(ev3dev::color_sensor::mode_rgb_raw);
        return value(1);
      }

      // Blue component of the detected color, in the range 0-1020.
      int blue(bool do_set_mode = true) {
        if (do_set_mode) set_mode(ev3dev::color_sensor::mode_rgb_raw);
        return value(2);
      }
  };

  class ultrasonic_sensor : public sensor {
    public:
      ultrasonic_sensor(address_type a) : sensor(a) {}
      float distance_centimeters(bool do_set_mode = true) {
        if (do_set_mode) set_mode(ev3dev::ultrasonic_sensor::mode_us_dist_cm);
        return float_value(0);
      }
      float distance_inches(bool do_set_mode = true) {
        if (do_set_mode) set_mode(ev3dev::ultrasonic_sensor::mode_us_dist_in);
        return float_value(0);
      }
  };

  class motor : protected device {
    public:
      typedef device_type motor_type;

      motor(address_type a) { device::connect("/sys/devices/lego-sensor/", "motor", {{ "address", { a }} }); }
      motor(address_type a, const motor_type & t) { device::connect("/sys/devices/lego-sensor/", "motor", {{ "address", { a }}, { "driver_name", { t }} }); }

      auto set_command(std::string v) -> decltype(*this) {
        set_attr_string("command", v);
        return *this;
      }

      std::string address() const { return get_attr_string("address"); }
      mode_set commands() const { return get_attr_set("commands"); }
      int count_per_rot() const { return get_attr_int("count_per_rot"); }
      int count_per_m() const { return get_attr_int("count_per_m"); }
      std::string driver_name() const { return get_attr_string("driver_name"); }
      int duty_cycle() const { return get_attr_int("duty_cycle"); }
      int duty_cycle_sp() const { return get_attr_int("duty_cycle_sp"); }
      auto set_duty_cycle_sp(int v) -> decltype(*this) {
        set_attr_int("duty_cycle_sp", v);
        return *this;
      }
      int full_travel_count() const { return get_attr_int("full_travel_count"); }
      std::string polarity() const { return get_attr_string("polarity"); }
      auto set_polarity(std::string v) -> decltype(*this) {
        set_attr_string("polarity", v);
        return *this;
      }
      int position() const { return get_attr_int("position"); }
      auto set_position(int v) -> decltype(*this) {
        set_attr_int("position", v);
        return *this;
      }
      int position_p() const { return get_attr_int("hold_pid/Kp"); }
      auto set_position_p(int v) -> decltype(*this) {
        set_attr_int("hold_pid/Kp", v);
        return *this;
      }
      int position_i() const { return get_attr_int("hold_pid/Ki"); }
      auto set_position_i(int v) -> decltype(*this) {
        set_attr_int("hold_pid/Ki", v);
        return *this;
      }
      int position_d() const { return get_attr_int("hold_pid/Kd"); }
      auto set_position_d(int v) -> decltype(*this) {
        set_attr_int("hold_pid/Kd", v);
        return *this;
      }
      int position_sp() const { return get_attr_int("position_sp"); }
      auto set_position_sp(int v) -> decltype(*this) {
        set_attr_int("position_sp", v);
        return *this;
      }
      int max_speed() const { return get_attr_int("max_speed"); }
      int speed() const { return get_attr_int("speed"); }
      int speed_sp() const { return get_attr_int("speed_sp"); }
      auto set_speed_sp(int v) -> decltype(*this) {
        set_attr_int("speed_sp", v);
        return *this;
      }
      int ramp_up_sp() const { return get_attr_int("ramp_up_sp"); }
      auto set_ramp_up_sp(int v) -> decltype(*this) {
        set_attr_int("ramp_up_sp", v);
        return *this;
      }
      int speed_p() const { return get_attr_int("speed_pid/Kp"); }
      auto set_speed_p(int v) -> decltype(*this) {
        set_attr_int("speed_pid/Kp", v);
        return *this;
      }
      int speed_i() const { return get_attr_int("speed_pid/Ki"); }
      auto set_speed_i(int v) -> decltype(*this) {
        set_attr_int("speed_pid/Ki", v);
        return *this;
      }
      int speed_d() const { return get_attr_int("speed_pid/Kd"); }
      auto set_speed_d(int v) -> decltype(*this) {
        set_attr_int("speed_pid/Kd", v);
        return *this;
      }
      mode_set state() const { return get_attr_set("state"); }
      std::string stop_action() const { return get_attr_string("stop_action"); }
      auto set_stop_action(std::string v) -> decltype(*this) {
        set_attr_string("stop_action", v);
        return *this;
      }
      mode_set stop_actions() const { return get_attr_set("stop_actions"); }
      int time_sp() const { return get_attr_int("time_sp"); }
      auto set_time_sp(int ms) -> decltype(*this) {
        set_attr_int("time_sp", ms);
        return *this;
      }
      void run_forever() { set_command("run-forever"); }
      void run_to_abs_pos() { set_command("run-to-abs-pos"); }
      void run_to_rel_pos() { set_command("run-to-rel-pos"); }
      void run_timed() { set_command("run-timed"); }
      void run_direct() { set_command("run-direct"); }
      void stop() { set_command("stop"); }
      void reset() { set_command("reset"); }
  };

  class large_motor : public motor {
    public:
      large_motor(address_type a) : motor(a, "lego-ev3-l-motor") {}
  };

  class medium_motor : public motor {
    public:
      medium_motor(address_type a) : motor(a, "lego-ev3-m-motor") {}
  };

} // namespace ev3mock

#ifndef __DEFINE_CUSTOM_BOUNCE
#define __DEFINE_CUSTOM_BOUNCE
#include <Arduino.h>

class CustomBounce {
private:
  bool current_state;
  bool public_state;
  signed long last_low;
  signed long last_high;
  int last_period_start;
public:
  CustomBounce(int pin);
  void handleInterrup();
  bool read();
  void update();
};
#endif

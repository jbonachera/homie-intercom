#include <CustomBounce.hpp>
using namespace std;

CustomBounce::CustomBounce(int pin){
  this->current_state = false;
  this->last_period_start = 0;
  this->last_low = 0;
  this->current_state = digitalRead(pin) == HIGH;

  if (!this->current_state){
    this->last_low = millis();
  }
}
void CustomBounce::handleInterrup(){
  this->current_state = !current_state;
  if (!this->current_state) { // "if we are LOW"
    this->last_low = millis();
  } else if (last_period_start == 0) {
    last_period_start = millis();
  }
}
bool CustomBounce::read(){

  if (millis() - this->last_low > 50) {
    last_period_start = 0;
  }
  return (last_period_start > 0 && millis() - last_period_start > 300);
}

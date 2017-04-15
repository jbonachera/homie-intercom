#include <Homie.h>
#include <CustomBounce.hpp>
#include <version.h>


#define PINSENSOR 13 //d7

bool last_state = false;

// The intercom is using a strange mecanism to announce someone is ringing, so we need a custom bounce logic.
CustomBounce bouncer(PINSENSOR);

HomieSetting<const char*> roomSetting("room", "The room this sensor will monitor"); 

HomieNode intercomNode("intercom", "intercom");

void setupHandler() {

  intercomNode.setProperty("unit").send("bool");
  intercomNode.setProperty("room").send(roomSetting.get());
  intercomNode.setProperty("ringing").setRetained(true).send("false");
}

void intercomLoopHander(){
  bool state = bouncer.read();
  if (state != last_state) {
    last_state = state;
    intercomNode.setProperty("ringing").setRetained(true).send(state ? "true" : "false");
  }
}

void loopHandler() {
  intercomLoopHander();
}

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;
  Homie_setFirmware("intercom", VERSION);
  Homie_setBrand("vx-labs")
  intercomNode.advertise("unit");
  intercomNode.advertise("room");
  intercomNode.advertise("ringing");
  Homie.setSetupFunction(setupHandler).setLoopFunction(loopHandler);
  // Yay, lambda !
  attachInterrupt(digitalPinToInterrupt(PINSENSOR), [](){
    bouncer.handleInterrup();
  }, CHANGE);
  roomSetting.setDefaultValue("NoRoom").setValidator([] (const char* candidate) {
    return true;
  });
  pinMode(PINSENSOR, INPUT);
  digitalWrite(PINSENSOR, LOW);
  Homie.setup();
}

void loop() {
  Homie.loop();
}

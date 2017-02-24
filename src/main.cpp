#include <Homie.h>

#define PINSENSOR 13
#define PINOUT 12
const int INTERCOM_INTERVAL = 500;
bool state = false;
bool future_state = false;
unsigned long lastPoll = 0;
unsigned long update_date = 0;


HomieSetting<const char*> roomSetting("room", "The room this sensor will monitor");  // id, description

HomieNode intercomNode("intercom", "intercom");


void setupHandler() {
  pinMode(PINSENSOR, INPUT_PULLUP);
  pinMode(PINOUT, OUTPUT);
  intercomNode.setProperty("unit").send("bool");
  intercomNode.setProperty("room").send(roomSetting.get());
}

void intercomLoopHander(){
  bool new_state = false;
  if (millis() - lastPoll >= INTERCOM_INTERVAL * 1UL) {
    new_state = digitalRead(PINSENSOR) == LOW;
    if (new_state != state) {
      future_state = new_state;
      update_date = millis();
    }
    else if (future_state != state) {
      if (millis() - update_date > 100){
        if (future_state) {
          intercomNode.setProperty("ringing").setRetained(true).send("true");
        } else {
          intercomNode.setProperty("ringing").setRetained(true).send("false");
        }
        state = future_state;
      }
    }
  }
  lastPoll = millis();
}

void loopHandler() {
  intercomLoopHander();
}

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;
  Homie_setFirmware("vx-intercom-sensor", "1.0.2");
  intercomNode.advertise("unit");
  intercomNode.advertise("room");
  intercomNode.advertise("ringing");
  Homie.setSetupFunction(setupHandler).setLoopFunction(loopHandler);

  roomSetting.setDefaultValue("NoRoom").setValidator([] (const char* candidate) {
    return true;
  });


  Homie.setup();
}

void loop() {
  Homie.loop();
}

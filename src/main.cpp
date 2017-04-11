#include <Homie.h>
#include <version.h>

#define PINSENSOR 13 //d7
#define SENSOR_IS_RINGING HIGH
#define INTERCOM_INTERVAL 100
bool state = true;
bool updated = false;
unsigned long lastPoll = 0;


HomieSetting<const char*> roomSetting("room", "The room this sensor will monitor");  // id, description

HomieNode intercomNode("intercom", "intercom");


void setupHandler() {
  pinMode(PINSENSOR, INPUT);
  intercomNode.setProperty("unit").send("bool");
  intercomNode.setProperty("room").send(roomSetting.get());
  intercomNode.setProperty("ringing").setRetained(true).send("false");
}

void toogle(){
  state = !state;
  updated = true;
}

void intercomLoopHander(){
  if (millis() - lastPoll >= INTERCOM_INTERVAL * 1UL) {
    if (updated) {
      if (state) {
        intercomNode.setProperty("ringing").setRetained(true).send("true");
      } else {
        intercomNode.setProperty("ringing").setRetained(true).send("false");
      }
      updated = false;
    }
    lastPoll = millis();
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

  roomSetting.setDefaultValue("NoRoom").setValidator([] (const char* candidate) {
    return true;
  });

  attachInterrupt(PINSENSOR, toogle, CHANGE);

  Homie.setup();
}

void loop() {
  Homie.loop();
}

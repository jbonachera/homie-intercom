#include <Homie.h>
#include <version.h>

#define PINSENSOR 13 //d7

int last_state = false;


HomieSetting<const char*> roomSetting("room", "The room this sensor will monitor");  // id, description

HomieNode intercomNode("intercom", "intercom");
Bounce debouncer = Bounce();

void setupHandler() {
  pinMode(PINSENSOR, INPUT);
  intercomNode.setProperty("unit").send("bool");
  intercomNode.setProperty("room").send(roomSetting.get());
  intercomNode.setProperty("ringing").setRetained(true).send("false");
}

void intercomLoopHander(){
  int state = debouncer.read();
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

  roomSetting.setDefaultValue("NoRoom").setValidator([] (const char* candidate) {
    return true;
  });

  debouncer.attach(PINSENSOR);
  debouncer.interval(10);
  Homie.setup();
}

void loop() {
  Homie.loop();
  debouncer.update();
}

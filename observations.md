# Investigations

the intercom device I choose to study provides the following features:
  * remote door opening: The device is able to remotly open the main door of the building.
  * voice call: the device allows its owner to initiate a voice conversation with a someone in the hall of the building.
  * buzzing: the device is able to ringing when a person in the hall is requesting a voice conversation, like a classic phone

After opening the device, we can see the following picture:

![open intercom](intercom_open.png)

After a long investigation, the following map was set:

  * Blue cable: buzzer, when the buzz button in the hall is pressed, this cable a serie of spikes of short-timed 15v spikes, to emulate alternative current, i suppose, so it is not possible to use debouncing when listening for a signal.
  * <disconnected>
  * Brown cable: Speaker, when someone is speaking from the hall, the signal is sent to the intercom through this cable
  * Yellow cable: Microphone, same as the speaker, but the other way
  * Black cable: Door interruptor, when the cable is pluged into the mass, the door from the hall opens
  * White cable: Mass

The map was determined by seeing which feature do we loose when disconnecting a cable. "All the features are gone" means you are dealing with the mass cable.

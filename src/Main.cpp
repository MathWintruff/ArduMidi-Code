#include <Arduino.h>
#include <MIDI.h> // by Francois Best
MIDI_CREATE_DEFAULT_INSTANCE();

byte midiChanel_POTs = 1;
byte midiChanel_Keypad = 1;
boolean retainMode = false;
const int btnChanelSwitch[2][2] = {{9,10},{11,12}}, potsChannelSwitch = 8, retainModeSwitch = 13;

#include <Potentiometers.h>
#include <MatrixKeypad.h>
#include <Switchs.h>


Potentiometer pots[]{A0, A1, A2, A3, A4, A5};
int potsQTD = 6;

int keypadRowPins[] = {7, 6};
int keypadCollumPins[] = {2, 3 ,4 ,5};
MatrixKeypad keypad(2, keypadRowPins, 4, keypadCollumPins);

void setup() {
  // 31250 for MIDI class compliant | 115200 for Hairless MIDI
  MIDI.begin(MIDI_CHANNEL_OFF);
  Serial.begin(31250);

}

void loop() {
    ChannelsSwitchsInit();
    ChannelRead();
    CheckPotsForMIDI(pots, potsQTD, midiChanel_POTs);
    CheckKeypadForMIDI(keypad, midiChanel_Keypad, retainMode);
    delay(1);

}
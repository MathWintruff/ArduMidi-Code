#include <Arduino.h>

void ChannelsSwitchsInit(){
  pinMode(btnChanelSwitch[0][0], INPUT_PULLUP);
  pinMode(btnChanelSwitch[0][1], INPUT_PULLUP);
  pinMode(btnChanelSwitch[1][0], INPUT_PULLUP);
  pinMode(btnChanelSwitch[1][1], INPUT_PULLUP);
  pinMode(potsChannelSwitch, INPUT_PULLUP);
  pinMode(retainModeSwitch, INPUT_PULLUP);
}
void ChannelRead(){
  boolean btnChanelSwitchReads[2][2] = {{!digitalRead(btnChanelSwitch[0][0]),!digitalRead(btnChanelSwitch[0][1])},{!digitalRead(btnChanelSwitch[1][0]),!digitalRead(btnChanelSwitch[1][1])}};
  boolean potsChannelSwitchRead = !digitalRead(potsChannelSwitch);
  boolean retainModeSwitchRead = !digitalRead(retainModeSwitch);

  btnChanelSwitchReads[0][0]&&btnChanelSwitchReads[1][0] ? midiChanel_Keypad = 1 :
  btnChanelSwitchReads[0][0]&&!btnChanelSwitchReads[1][0]&&!btnChanelSwitchReads[1][1] ? midiChanel_Keypad = 2 :
  btnChanelSwitchReads[0][0]&&btnChanelSwitchReads[1][1] ? midiChanel_Keypad = 3 :

  !btnChanelSwitchReads[0][0]&&!btnChanelSwitchReads[0][1]&&btnChanelSwitchReads[1][0] ? midiChanel_Keypad = 4 :
  !btnChanelSwitchReads[0][0]&&!btnChanelSwitchReads[0][1]&&!btnChanelSwitchReads[1][0]&&!btnChanelSwitchReads[1][1] ? midiChanel_Keypad = 5 :
  !btnChanelSwitchReads[0][0]&&!btnChanelSwitchReads[0][1]&&btnChanelSwitchReads[1][1] ? midiChanel_Keypad = 6 :

  btnChanelSwitchReads[0][1]&&btnChanelSwitchReads[1][0] ? midiChanel_Keypad = 7 :
  btnChanelSwitchReads[0][1]&&!btnChanelSwitchReads[1][0]&&!btnChanelSwitchReads[1][1] ? midiChanel_Keypad = 8 :
  btnChanelSwitchReads[0][1]&&btnChanelSwitchReads[1][1] ? midiChanel_Keypad = 9 : midiChanel_Keypad = 1;

  potsChannelSwitchRead ? midiChanel_POTs = 1 : midiChanel_POTs = 2;

  retainModeSwitchRead ? retainMode = true : retainMode = false;

}
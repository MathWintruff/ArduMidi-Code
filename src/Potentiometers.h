#include <Arduino.h>

class Potentiometer {
    private:
        int _Pin;
        int _lastReading;
        const int _trashHold = 5;

    public:
        Potentiometer(const int Pin);
        boolean HaveChanged();
        int CurrentValue();
};

Potentiometer::Potentiometer(const int Pin){
    _Pin = Pin;
    _lastReading = analogRead(_Pin);
}

boolean Potentiometer::HaveChanged(){
    return (abs(analogRead(_Pin) - _lastReading) > _trashHold) ? true : false;
}

int Potentiometer::CurrentValue(){
    int reading = analogRead(_Pin);
    _lastReading = reading;
    return reading >= 1018 ? 1023 : reading <= 6 ? 0 : reading;
}

void CheckPotsForMIDI(Potentiometer pots[], int qtdPots, byte channel){
    for(int i =0; i < qtdPots; i++){
        if(pots[i].HaveChanged()){
            MIDI.sendControlChange(i+1, map(pots[i].CurrentValue(), 0, 1023, 0, 127), channel);
        }
        delay(1);
    } 

}
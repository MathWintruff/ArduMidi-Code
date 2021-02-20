#include <Arduino.h>

struct ReadingResult{
            boolean wasClicked = false;
            boolean isBeingClicked = false;
            byte btnNumber = 0;
};

class MatrixKeypad {

    private:
        int _qtdRows;
        int _rowPins[100];
        int _qtdColluns;
        int _collunPins[100];
        ReadingResult _currentBtnReading;
        ReadingResult _previousBtnReading;       

    public:
        MatrixKeypad(int _qtdRows, int _rowPins[], int _qtdColluns, int _collunPins[]);
        void init();
        ReadingResult ReadKeypad();

};


        MatrixKeypad::MatrixKeypad(int qtdRows, int rowPins[], int qtdColluns, int collunPins[]){
            _qtdRows = qtdRows;
            _qtdColluns = qtdColluns;
            for(int row = 0; row < qtdRows; row++){
                _rowPins[row] = rowPins[row];
            }
            for(int collum = 0; collum < _qtdColluns; collum++){
                _collunPins[collum] = collunPins[collum];
            }

            init();
        }

        void MatrixKeypad::init(){
            for(int row = 0; row < _qtdRows; row++){
                pinMode(_rowPins[row], OUTPUT);
                digitalWrite(_rowPins[row], HIGH);
            }
            for(int collum = 0; collum < _qtdColluns; collum++){
                pinMode(_collunPins[collum], INPUT_PULLUP);
            };
        }

        

        ReadingResult MatrixKeypad::ReadKeypad(){
            _currentBtnReading.isBeingClicked = false;
            for(int row = 0; row < _qtdRows; row++){
                digitalWrite(_rowPins[row], LOW);
                for(int collum = 0; collum < _qtdColluns; collum++){
                    if(!digitalRead(_collunPins[collum])){
                        _currentBtnReading.isBeingClicked = true;
                        _currentBtnReading.btnNumber = ((row * _qtdColluns)+ collum + 1);
                    }   
                }
                digitalWrite(_rowPins[row], HIGH);
            }
            _currentBtnReading.isBeingClicked == _previousBtnReading.isBeingClicked ? _currentBtnReading.wasClicked = false : _currentBtnReading.wasClicked = true;
            _previousBtnReading = _currentBtnReading;
            return _currentBtnReading;
        }

void CheckKeypadForMIDI(MatrixKeypad keypad, byte channel){
    byte noteVelocity;
    ReadingResult keypadReading = keypad.ReadKeypad();
    if(keypadReading.wasClicked){
        keypadReading.isBeingClicked ? noteVelocity = 127 : noteVelocity = 0;
        MIDI.sendNoteOn(keypadReading.btnNumber, noteVelocity, channel);
    }
}
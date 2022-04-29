#include <Arduino.h>
#include "IC_Tester.h"

IC_Tester icTest;
int incomingByte = 0;
bool bad_input = true;
int gate;
void setup() {
    Serial.begin(9600);
}

void loop() {
    bad_input = true;
    gate = -1;
    while (bad_input){
        Serial.println("Enter Gate type as number: \nLS02 - 0\nLS04 - 1\nLS08 - 2\nLS32 - 3");
        if (Serial.available() > 0) {
            // read the incoming byte:
            incomingByte = Serial.read();
            switch (incomingByte) {
                case 0:
                    gate = NOR;
                    break;
                case 1:
                    gate = NOT;
                    bad_input = false
                    break;
                case 2:
                    gate = AND;
                    bad_input = false;
                    break;
                case 3:
                    gate = OR;
                    bad_input = false;
                    break;
                default:
                    Serial.println("Invalid IC type. Try Again.");
            }
            if(!bad_input){
                icTest.scan(gate);
            }
        }
    }
}

#include <Arduino.h>
#include "../include/IC_Tester.h"

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
    Serial.println("Enter Gate type as number: \nLS02 - 0\nLS04 - 1\nLS08 - 2\nLS32 - 3");
    while (bad_input) {
        if (Serial.available() > 0) {
            // read the incoming byte:
            incomingByte = Serial.read();
            switch (incomingByte) {
                case 48:
                    gate = NOR;
                    bad_input = false;
                    break;
                case 49:
                    gate = NOT;
                    bad_input = false;
                    break;
                case 50:
                    gate = AND;
                    bad_input = false;
                    break;
                case 51:
                    gate = OR;
                    bad_input = false;
                    break;
                default:
                    Serial.println("Invalid IC type. Try Again.");
                    Serial.println("Enter Gate type as number: \nLS02 - 0\nLS04 - 1\nLS08 - 2\nLS32 - 3");
            }
            if (!bad_input) {
                icTest.scan(gate);
            }

        }
    }
}
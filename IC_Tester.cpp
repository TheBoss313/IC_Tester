//
// Created by vlad on 29/04/22.
// GPIO 0-12 inclusive are "Data", GPIO 13 is controllable power
#include "IC_Tester.h"
#include <Arduino.h>

IC_Tester::IC_Tester() :
notList([TO_IC, FROM_IC, TO_IC, FROM_IC, TO_IC, FROM_IC, GND, FROM_IC, TO_IC, FROM_IC, TO_IC, FROM_IC, TO_IC, VCC]),
andList([TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, FROM_IC, GND, FROM_IC, TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, VCC]),
orList([TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, FROM_IC, GND, FROM_IC, TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, VCC]),
norList([FROM_IC, TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, GND, TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, FROM_IC, VCC]),
pinList([0, 1, 2, 3, 4, 5, 6, ARD_GND, 7, 8, 9, 10, 11, 12, ARD_VCC]),
andGates([[0, 1, 2], [3, 4, 5], [7, 8 , 9], [10, 11, 12]]),
norGates([[0, 1, 2], [3, 4, 5], [7, 8 , 9], [10, 11, 12]]),
orGates([[0, 1, 2], [3, 4, 5], [7, 8 , 9], [10, 11, 12]]),
notGates([[0, 1], [2, 3], [4, 5], [7, 8], [9, 10], [11, 12]])

{
}
void IC_Tester::setPins(const int gateList[14]){
    for (int i = 0; i < 14; i++) {
        if (gateList[i] == TO_IC){
            pinMode(pinList[i], OUTPUT);
        }else if (gateList[i] == FROM_IC){
            pinMode(pinList[i], INPUT)
        }else if (gateList[i] == VCC){
            pinMode(pinList[i], OUTPUT);
        }
    }
}

void IC_Tester::scan(const int gate) {
    bool test_res;
    switch (gate) {
        case OR:
            // case follows scheme [in, in, out]
            int cases[4][3] = [[LOW, LOW, LOW],[LOW,HIGH, HIGH],[HIGH, LOW, HIGH],[HIGH, HIGH, HIGH]];
            setPins(orList);
            // power to VCC
            digitalWrite(ARD_VCC, HIGH);
            gates = orGates;
            list = orList;
            break;
        case AND:
            setPins(andList);
            break;
        case NOR:
            setPins(norList);
            break;
        case NOT:
            setPins(notList);
            break;
    }
    switch (gate) {
        case OR:
        case NOR:
        case AND:
            int test_outputs[4][4];
        for (int gateI = 0; gateI < 4; gateI++) {
            int locGate = gates[gateI]; // [0, 1, 2]

            for (int test = 0; test < 4; test++) {
                if (list[locGate[0]] == TO_IC) {
                    digitalWrite(list[locGate], cases[test][0]);
                }
                if (list[locGate[1]] == TO_IC) {
                    digitalWrite(list[locGate], cases[test][1]);
                }
                if (list[locGate[2]] == TO_IC) {
                    digitalWrite(list[locGate], cases[test][2]);
                }
                if (list[locGate[0]] == FROM_IC) {
                    test_res = digitalRead(list[locGate]) == cases[test][0];
                    test_outputs[gateI][test] = test_res;
                }
                if (list[locGate[1]] == FROM_IC) {
                    test_res = digitalRead(list[locGate]) == cases[test][1];
                    test_outputs[gateI][test] = test_res;
                }
                if (list[locGate[2]] == FROM_IC) {
                    test_res = digitalRead(list[locGate]) == cases[test][2];
                    test_outputs[gateI][test] = test_res;
                }
            }
        }
        break;
        case NOT:
            for (int gateI = 0; gateI < 6; gateI++) {
                for (int test = 0; test < 6; test++) {
                    if (gates[gateI][0]) {}
                }
            }
            break;
    }
    // Printed Output
    for (int i = 0; i < test_outputs.length; i++) {
        Serial.println("Gate #"+(i+1));
        for (int j=0;j<test_outputs[0].length; j++){
            String out = "";
            if (test_outputs[i][j]){
                out = "PASS";
            }else{
                out = "FAIL";
            }
            Serial.println("Condition "+(j+1)+out);
        }
    }
}
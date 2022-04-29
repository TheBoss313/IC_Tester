//
// Created by vlad on 29/04/22.
// GPIO 0-12 inclusive are "Data", GPIO 13 is controllable power
#include "../include/IC_Tester.h"
#include <Arduino.h>


IC_Tester::IC_Tester() : notList{TO_IC, FROM_IC, TO_IC, FROM_IC, TO_IC, FROM_IC, GND, FROM_IC, TO_IC, FROM_IC, TO_IC,
                                 FROM_IC, TO_IC, VCC},
                         andList{TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, FROM_IC, GND, FROM_IC, TO_IC, TO_IC, FROM_IC,
                                 TO_IC, TO_IC, VCC},
                         orList{TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, FROM_IC, GND, FROM_IC, TO_IC, TO_IC, FROM_IC,
                                TO_IC, TO_IC, VCC},
                         norList{FROM_IC, TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, GND, TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC,
                                 FROM_IC, VCC},
                         pinList{0, 1, 2, 3, 4, 5, ARD_GND, 6, 7, 8, 9, 10, 11, ARD_VCC},
                         andGates{{0,  1,  2},
                                  {3,  4,  5},
                                  {7,  8,  9},
                                  {10, 11, 12}},
                         orGates{{0,  1,  2},
                                 {3,  4,  5},
                                 {7,  8,  9},
                                 {10, 11, 12}},
                         norGates{{0,  1,  2},
                                  {3,  4,  5},
                                  {7,  8,  9},
                                  {10, 11, 12}},
                         notGates{{0,  1},
                                  {2,  3},
                                  {4,  5},
                                  {7,  8},
                                  {9,  10},
                                  {11, 12}} {
}

void IC_Tester::setPins(const int gateList[14]) {
    for (int i = 0; i < 14; i++) {
        if (gateList[i] == TO_IC) {
            pinMode(pinList[i], OUTPUT);
        } else if (gateList[i] == FROM_IC) {
            pinMode(pinList[i], INPUT);
        } else if (gateList[i] == VCC) {
            pinMode(pinList[i], OUTPUT);
        }
    }
}

void IC_Tester::scan(const int gate) {
    bool test_res;
    int gates[4][3];
    int list[14];
    int cases[4][3];
    if (gate == OR) {
        // case follows scheme [in, in, out]
        int cases[4][3] = {{LOW,  LOW,  LOW},
                           {LOW,  HIGH, HIGH},
                           {HIGH, LOW,  HIGH},
                           {HIGH, HIGH, HIGH}};
        setPins(orList);
        // power to VCC
        digitalWrite(ARD_VCC, HIGH);
        for (unsigned int i = 0; i < sizeof(orGates); i++) {
            for (unsigned int j = 0; j < sizeof(orGates[0]); j++) {
                gates[i][j] = orGates[i][j];
            }
        }
        for (unsigned int i = 0; i < sizeof(orList); i++) {
            list[i] = orList[i];
        }
    } else if (gate == AND) {
        // case follows scheme [in, in, out]
        int cases[4][3] = {{LOW,  LOW,  LOW},
                           {LOW,  HIGH, LOW},
                           {HIGH, LOW,  LOW},
                           {HIGH, HIGH, HIGH}};
        setPins(andList);
        // power to VCC
        digitalWrite(ARD_VCC, HIGH);
        for (unsigned int i = 0; i < sizeof(andGates); i++) {
            for (unsigned int j = 0; j < sizeof(andGates[0]); j++) {
                gates[i][j] = andGates[i][j];
            }
        }
        for (unsigned int i = 0; i < sizeof(andList); i++) {
            list[i] = andList[i];
        }
    } else if (gate == NOR) {
        // case follows scheme [in, in, out]
        int cases[4][3] = {{LOW,  LOW,  HIGH},
                           {LOW,  HIGH, LOW},
                           {HIGH, LOW,  LOW},
                           {HIGH, HIGH, LOW}};
        setPins(norList);
        // power to VCC
        digitalWrite(ARD_VCC, HIGH);
        for (unsigned int i = 0; i < sizeof(norGates); i++) {
            for (unsigned int j = 0; j < sizeof(norGates[0]); j++) {
                gates[i][j] = norGates[i][j];
            }
        }
        for (unsigned int i = 0; i < sizeof(norList); i++) {
            list[i] = norList[i];
        }
    } else if (gate == NOT) {
        // case follows scheme [in, in, out]
        int cases[4][3] = {{LOW,  LOW,  LOW},
                           {LOW,  HIGH, HIGH},
                           {HIGH, LOW,  HIGH},
                           {HIGH, HIGH, HIGH}};
        setPins(notList);
        // power to VCC
        digitalWrite(ARD_VCC, HIGH);
        for (unsigned int i = 0; i < sizeof(notGates); i++) {
            for (unsigned int j = 0; j < sizeof(notGates[0]); j++) {
                gates[i][j] = notGates[i][j];
            }
        }
        for (unsigned int i = 0; i < sizeof(notList); i++) {
            list[i] = notList[i];
        }
    }
    if (gate == AND || gate == OR || gate == NOR) {
        int test_outputs[4][4];
        for (int gateI = 0; gateI < 4; gateI++) {
            int locGate[3];
            for (int i = 0; i < 3; i++) {
                locGate[i] = gates[gateI][i];
            }

            for (int test = 0; test < 4; test++) {
                if (list[locGate[0]] == TO_IC) {
                    digitalWrite(list[locGate[0]], cases[test][0]);
                }
                if (list[locGate[1]] == TO_IC) {
                    digitalWrite(list[locGate[0]], cases[test][1]);
                }
                if (list[locGate[2]] == TO_IC) {
                    digitalWrite(list[locGate[0]], cases[test][2]);
                }
                if (list[locGate[0]] == FROM_IC) {
                    test_res = digitalRead(list[locGate[0]]) == cases[test][0];
                    test_outputs[gateI][test] = test_res;
                }
                if (list[locGate[1]] == FROM_IC) {
                    test_res = digitalRead(list[locGate[0]]) == cases[test][1];
                    test_outputs[gateI][test] = test_res;
                }
                if (list[locGate[2]] == FROM_IC) {
                    test_res = digitalRead(list[locGate[0]]) == cases[test][2];
                    test_outputs[gateI][test] = test_res;
                }
            }
        }
        for (unsigned int i = 0; i < sizeof(test_outputs); i++) {
            Serial.print("Gate #");
            Serial.println(i + 1);
            for (unsigned int j = 0; j < sizeof(test_outputs[0]); j++) {
                String out = "";
                if (test_outputs[i][j]) { out = "PASS"; } else { out = "FAIL"; }
                Serial.print("Condition ");
                Serial.print(j + 1);
                Serial.println(out);
            }
        }
    } else if (gate == NOT) {
        int test_outputs[6][2];
        for (int gateI = 0; gateI < 6; gateI++) {
            for (int test = 0; test < 6; test++) {
                if (gates[gateI][0]) {}
            }
        }
        for (unsigned int i = 0; i < sizeof(test_outputs); i++) {
            Serial.print("Gate #");
            Serial.println(i + 1);
            for (unsigned int j = 0; j < sizeof(test_outputs[0]); j++) {
                String out = "";
                if (test_outputs[i][j]) { out = "PASS"; } else { out = "FAIL"; }
                Serial.print("Condition ");
                Serial.print(j + 1);
                Serial.println(out);
            }
        }
    }
    digitalWrite(ARD_VCC, LOW);
}
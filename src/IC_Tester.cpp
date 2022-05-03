//
// Created by vlad on 29/04/22.
// GPIO 2-13 inclusive are "Data", no controllable power
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
                         pinList{2, 3, 4, 5, 6, 7, ARD_GND, 8, 9, 10, 11, 12, 13, ARD_VCC},
                         andGates{{0,  1,  2},
                                  {3,  4,  5},
                                  {9,  8,  7},
                                  {12, 11, 10}},
                         orGates{{0,  1,  2},
                                 {3,  4,  5},
                                 {9,  8,  7},
                                 {12, 11, 10}},
                         norGates{{2,  1,  0},
                                  {5,  4,  3},
                                  {7,  8,  9},
                                  {10, 11, 12}},
                         notGates{{0,  1},
                                  {2,  3},
                                  {4,  5},
                                  {8,  7},
                                  {10, 9},
                                  {12, 11}} {
}

void IC_Tester::setPins(const int gateList[14]) {
    for (int i = 0; i < 14; i++) {
        if (gateList[i] == TO_IC) {
            pinMode(pinList[i], OUTPUT);
        } else if (gateList[i] == FROM_IC) {
            pinMode(pinList[i], INPUT);
        } //else if (gateList[i] == VCC) {
        //pinMode(pinList[i], OUTPUT);
        //}
    }
}

void IC_Tester::scan(const int gate) {
    bool test_res;
    // Power to VCC
    // digitalWrite(ARD_VCC, HIGH);
    if (gate == OR) {
        Serial.println("Scanning OR gate...");
        // case follows scheme [in, in, out]
        int cases[4][3] = {{LOW,  LOW,  LOW},
                           {LOW,  HIGH, HIGH},
                           {HIGH, LOW,  HIGH},
                           {HIGH, HIGH, HIGH}};
        setPins(orList);
        int test_outputs[4][4];
        for (int gateI = 0; gateI < 4; gateI++) {
            int locGate[3];
            for (int i = 0; i < 3; i++) {
                locGate[i] = orGates[gateI][i];
            }

            for (int test = 0; test < 4; test++) {
                digitalWrite(pinList[locGate[0]], cases[test][0]);
                digitalWrite(pinList[locGate[1]], cases[test][1]);
                test_res = digitalRead(pinList[locGate[2]]) == cases[test][2];
                Serial.print(digitalRead(pinList[locGate[2]]));
                Serial.print(" ");
                Serial.print(cases[test][2]);
                Serial.print(" ");
                Serial.println(test_res);
                test_outputs[gateI][test] = test_res;
            }
        }
        // Printer Loop
        for (int i = 0; i < 4; i++) {
            Serial.print("Gate #");
            Serial.println(i + 1);
            int counter = 1;
            for (int j = 0; j < 4; j++) {
                String out = "";
                if (test_outputs[i][j]) { out = "PASS"; } else { out = "FAIL"; }
                Serial.print("Condition ");
                Serial.print(counter);
                Serial.print(" ");
                Serial.println(out);
                counter++;
            }
        }
    }
    else if (gate == AND) {
        Serial.println("Scanning AND gate...");
        // case follows scheme [in, in, out]
        int cases[4][3] = {{LOW,  LOW,  LOW},
                           {LOW,  HIGH, LOW},
                           {HIGH, LOW,  LOW},
                           {HIGH, HIGH, HIGH}};
        setPins(andList);
        int test_outputs[4][4];
        for (int gateI = 0; gateI < 4; gateI++) {
            int locGate[3];
            for (int i = 0; i < 3; i++) {
                locGate[i] = andGates[gateI][i];
            }

            for (int test = 0; test < 4; test++) {
                digitalWrite(pinList[locGate[0]], cases[test][0]);
                digitalWrite(pinList[locGate[1]], cases[test][1]);
                test_res = digitalRead(pinList[locGate[2]]) == cases[test][2];
                Serial.print(digitalRead(pinList[locGate[2]]));
                Serial.print(" ");
                Serial.print(cases[test][2]);
                Serial.print(" ");
                Serial.println(test_res);
                test_outputs[gateI][test] = test_res;
            }
        }
        // Printer Loop
        for (int i = 0; i < 4; i++) {
            Serial.print("Gate #");
            Serial.println(i + 1);
            int counter = 1;
            for (int j = 0; j < 4; j++) {
                String out = "";
                if (test_outputs[i][j]) { out = "PASS"; } else { out = "FAIL"; }
                Serial.print("Condition ");
                Serial.print(counter);
                Serial.print(" ");
                Serial.println(out);
                counter++;
            }
        }
    }
    else if (gate == NOR) {
        Serial.println("Scanning NOR gate...");
        // case follows scheme [in, in, out]
        int cases[4][3] = {{LOW,  LOW,  HIGH},
                           {LOW,  HIGH, LOW},
                           {HIGH, LOW,  LOW},
                           {HIGH, HIGH, LOW}};
        setPins(norList);
        int test_outputs[4][4];
        for (int gateI = 0; gateI < 4; gateI++) {
            int locGate[3];
            for (int i = 0; i < 3; i++) {
                locGate[i] = norGates[gateI][i];
            }

            for (int test = 0; test < 4; test++) {
                digitalWrite(pinList[locGate[0]], cases[test][0]);
                digitalWrite(pinList[locGate[1]], cases[test][1]);
                test_res = digitalRead(pinList[locGate[2]]) == cases[test][2];
                Serial.print(digitalRead(pinList[locGate[2]]));
                Serial.print(" ");
                Serial.print(cases[test][2]);
                Serial.print(" ");
                Serial.println(test_res);
                test_outputs[gateI][test] = test_res;
            }
        }
        // Printer Loop
        for (int i = 0; i < 4; i++) {
            Serial.print("Gate #");
            Serial.println(i + 1);
            int counter = 1;
            for (int j = 0; j < 4; j++) {
                String out = "";
                if (test_outputs[i][j]) { out = "PASS"; } else { out = "FAIL"; }
                Serial.print("Condition ");
                Serial.print(counter);
                Serial.print(" ");
                Serial.println(out);
                counter++;
            }
        }
    }
    else if (gate == NOT) {
        Serial.println("Scanning NOT gate...");
        // case follows scheme [in, out]
        int cases[2][2] = {{HIGH, LOW},
                           {LOW,  HIGH}};
        setPins(notList);
        int test_outputs[6][2];
        for (int gateI = 0; gateI < 6; gateI++) {
            int locGate[2];
            for (int i = 0; i < 2; i++) {
                locGate[i] = notGates[gateI][i];
            }

            for (int test = 0; test < 2; test++) {
                digitalWrite(pinList[locGate[0]], cases[test][0]);
                test_res = digitalRead(pinList[locGate[1]]) == cases[test][1];
                Serial.print(digitalRead(pinList[locGate[1]]));
                Serial.print(" ");
                Serial.print(cases[test][1]);
                Serial.print(" ");
                Serial.println(test_res);
                test_outputs[gateI][test] = test_res;
            }
        }
        // Printer Loop
        for (int i = 0; i < 6; i++) {
            Serial.print("Gate #");
            Serial.println(i + 1);
            int counter = 1;
            for (int j = 0; j < 2; j++) {
                String out = "";
                if (test_outputs[i][j]) { out = "PASS"; } else { out = "FAIL"; }
                Serial.print("Condition ");
                Serial.print(counter);
                Serial.print(" ");
                Serial.println(out);
                counter++;
            }
        }
    }
    // digitalWrite(ARD_VCC, LOW);
}
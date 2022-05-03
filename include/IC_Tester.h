//
// Created by vlad on 29/04/22.
//

#ifndef IC_TESTER_IC_TESTER_H
#define IC_TESTER_IC_TESTER_H
#define TO_IC 90
#define FROM_IC 91
#define VCC 80
#define GND 81
#define NOT 4
#define AND 8
#define OR 32
#define NOR 2
#define ARD_GND -1
#define ARD_VCC 13

class IC_Tester {
private:
protected:
    int notList[14], andList[14], orList[14], norList[14], pinList[14], andGates[4][3], orGates[4][3], norGates[4][3], notGates[6][2];

    void setPins(const int gateList[14]);
public:
    IC_Tester();

    void scan(int gate);
};

#endif //IC_TESTER_IC_TESTER_H

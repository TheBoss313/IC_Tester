//
// Created by vlad on 29/04/22.
//

#ifndef IC_TESTER_IC_TESTER_H
#define IC_TESTER_IC_TESTER_H
#define TO_IC 2
#define FROM_IC 3
#define VCC 1
#define GND 0
#define NOT 0
#define AND 1
#definr OR 2
#define NOR 3
#define ARD_GND -1
#define ARD_VCC 13

class IC_Tester {
private:
protected:
    int[14] notList, andList, orList, norList, pinList;
    int[4][3] andGates, orGates, norGates;
    int[6][2] notGates;

    void scan(const int gate);

    void setPins(const int gateList[14]);
}

#endif //IC_TESTER_IC_TESTER_H

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

class IC_Tester {
private:
protected:

    int[14] notList, andList, orList, norList;

    void Scan(const int gate);
}

#endif //IC_TESTER_IC_TESTER_H

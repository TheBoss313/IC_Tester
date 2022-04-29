//
// Created by vlad on 29/04/22.
//
#include "IC_Tester.h"
#include <Arduino.h>

IC_Tester::IC_Tester() :
notList([TO_IC, FROM_IC, TO_IC, FROM_IC, TO_IC, FROM_IC, GND, FROM_IC, TO_IC, FROM_IC, TO_IC, FROM_IC, TO_IC, VCC]),
andList([TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, FROM_IC, GND, FROM_IC, TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, VCC]),
orList([TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, FROM_IC, GND, FROM_IC, TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, VCC]),
norList([FROM_IC, TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, GND, TO_IC, TO_IC, FROM_IC, TO_IC, TO_IC, FROM_IC, VCC])
{
}

void IC_Tester::notScan(void){

}
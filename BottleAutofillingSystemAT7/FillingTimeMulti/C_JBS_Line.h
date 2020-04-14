/* 
* C_JBS_Line.h
*
* Created: 13/04/2020 17:47:42
* Author: JB_Notebook
*/

#include <Arduino.h>

#ifndef __C_JBS_LINE_H__
#define __C_JBS_LINE_H__


class C_JBS_Line
{
//variables
public:
protected:
private:
uint8_t mu8_ValvePin;
uint8_t mu8_BtCalPin;
uint8_t mu8_CtPin;

bool mb_V;

bool mb_BtCal;
bool mb_BtCalLast;
bool mb_BtCalClick; 

bool mb_Ct;
bool mb_CtLast;

bool mb_BottleEmpty;

uint32_t mu32_AI_Color;
uint32_t mu32_SI_Color;
uint8_t mu8_SI_Blink;

//functions
public:
	C_JBS_Line();
	~C_JBS_Line();

    void Init(uint8_t u8_ValvePin, uint8_t u8_BtCalPin, uint8_t u8_CtPin);
    void Reset();
    void UpdateInput();

protected:
private:
	C_JBS_Line( const C_JBS_Line &c );
	C_JBS_Line& operator=( const C_JBS_Line &c );

}; //C_JBS_Line

#endif //__C_JBS_LINE_H__

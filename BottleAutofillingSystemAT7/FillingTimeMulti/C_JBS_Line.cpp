/* 
* C_JBS_Line.cpp
*
* Created: 13/04/2020 17:47:41
* Author: JB_Notebook
*/


#include "C_JBS_Line.h"

// default constructor
C_JBS_Line::C_JBS_Line():
    mu8_ValvePin{0u},
    mu8_BtCalPin{0u},
    mu8_CtPin{0u},
    mb_V{0u},
    mb_BtCal{1u},
    mb_BtCalLast{1u},
    mb_Ct{1u},
    mb_CtLast{1u},
    mb_BottleEmpty{1u},
    mu32_AI_Color{0u},
    mu32_SI_Color{0u},
    mu8_SI_Blink{0u},
    mb_BtCalClick{0u}
{
} //C_JBS_Line

// default destructor
C_JBS_Line::~C_JBS_Line()
{
} //~C_JBS_Line

void C_JBS_Line::Init(uint8_t u8_ValvePin, uint8_t u8_BtCalPin, uint8_t u8_CtPin)
{
    mu8_ValvePin = u8_ValvePin;
    mu8_BtCalPin = u8_BtCalPin;
    mu8_CtPin = u8_CtPin;
}

void C_JBS_Line::Reset()
{
    mb_V = 0u;
    
    mb_BtCal = 1u;
    mb_BtCalLast = 1u;
    mb_BtCalClick = 0u;
    
    mb_Ct = 1u;
    mb_CtLast = 1u;

    mb_BottleEmpty = 1u;
    mu32_AI_Color = 0u;
    mu32_SI_Color = 0u;
    mu8_SI_Blink = 0u;
}

void C_JBS_Line::UpdateInput()
{

}

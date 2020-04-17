/* 
* C_JBS_FillingSystem.cpp
*
* Created: 15/04/2020 18:09:24
* Author: JB
*/


#include "C_JBS_FillingSystem.h"

// default constructor
C_JBS_FillingSystem::C_JBS_FillingSystem()
{
} //C_JBS_FillingSystem

// default destructor
C_JBS_FillingSystem::~C_JBS_FillingSystem()
{
} //~C_JBS_FillingSystem

void C_JBS_FillingSystem::Init(const uint8_t u8_PedalePin, const uint8_t* pu8_ValvePin, const uint8_t* pu8_BtCalPin, const uint8_t* pu8_CtPin, C_JBS_LedNeoPixel* p_Leds)
{
    mu8_BtPedalePin = u8_PedalePin;
    mp_Leds = p_Leds;
    
    for(uint8_t u8_Index{0u}; u8_Index < JBS_NUMBER_LINES; u8_Index++)
    {
        m_Lines[u8_Index].Init(*pu8_ValvePin, *pu8_BtCalPin, *pu8_CtPin);
        pu8_ValvePin++;
        pu8_BtCalPin++;
        pu8_CtPin++;
    }
}

void C_JBS_FillingSystem::Reset()
{
    mb_BtPedale = 1u;
    mb_BtPedaleLast = 1u;
    mb_BtPedaleClick = 0u;
    
    for(uint8_t u8_Index{0u}; u8_Index < JBS_NUMBER_LINES; u8_Index++)
    {
        m_Lines[u8_Index].Reset();
    }
    
    mb_CleaningActive = 0u;
}

void C_JBS_FillingSystem::UpdateInput()
{
    mb_BtPedale = digitalRead(mu8_BtPedalePin);
    if( mb_BtPedale != mb_BtPedaleLast)
    {
        mb_BtPedaleLast = mb_BtPedale;
        mb_BtPedaleClick = !mb_BtPedale;
    }
    else
    {
        mb_BtPedaleClick = 0u;
    }
    
    for(uint8_t u8_Index{0u}; u8_Index < JBS_NUMBER_LINES; u8_Index++)
    {
        m_Lines[u8_Index].UpdateInput();
    }            
}


void C_JBS_FillingSystem::Manual()
{
    for(uint8_t u8_Index{0u}; u8_Index < JBS_NUMBER_LINES; u8_Index++)
    {
        m_Lines[u8_Index].Manual();
    }
}


void C_JBS_FillingSystem::SemiAuto()
{
    
}

void C_JBS_FillingSystem::Cleaning()
{
    mb_CleaningActive ^= mb_BtPedaleClick;
    
    if(mb_CleaningActive)
    {
        if(mb_BtPedaleClick)
        {
            //mu32_TimeKeeper = 
        }    
    }
}

void C_JBS_FillingSystem::WriteOutput()
{
    
    
    for(uint8_t u8_Index{0u}; u8_Index < JBS_NUMBER_LINES; u8_Index++)
    {
        m_Lines[u8_Index].WriteOutput();
    }
}

int8_t C_JBS_FillingSystem:: GetBtCalPressed(const uint8_t u8_Line) const
{
    
    int8_t i8_BtCalPressed{-1};
    if(u8_Line>0 && u8_Line<=JBS_NUMBER_LINES)
    {
        i8_BtCalPressed = m_Lines[u8_Line-1].GetBtCal();
    }    
    
    return i8_BtCalPressed;
}
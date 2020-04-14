/* 
* C_JBS_LedNeoPixel.h
*
* Created: 13/04/2020 13:46:50
* Author: JB_Notebook
*/

#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#ifndef __C_JBS_LEDNEOPIXEL_H__
#define __C_JBS_LEDNEOPIXEL_H__

const uint8_t U8_JBS_LED_NEO_PIXEL_DATA_PIN {1u};       // Data pin for Neo pixel led
const uint8_t U8_JBS_LED_NEO_PIXEL_NUMBER_LED {1u};//{8u}; // Number of used led in chain

class C_JBS_LedNeoPixel: public Adafruit_NeoPixel
{
//variables
public:
protected:
private:

//functions
public:
	C_JBS_LedNeoPixel();
	~C_JBS_LedNeoPixel();

    void init();
protected:
private:
	C_JBS_LedNeoPixel( const C_JBS_LedNeoPixel &c );
	C_JBS_LedNeoPixel& operator=( const C_JBS_LedNeoPixel &c );

}; //C_JBS_LedNeoPixel

#endif //__C_JBS_LEDNEOPIXEL_H__

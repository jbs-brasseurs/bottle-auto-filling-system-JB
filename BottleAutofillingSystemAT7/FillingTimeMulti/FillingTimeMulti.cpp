/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <Arduino_FreeRTOS.h>

#include "IO_Mapping.h"
#include "C_JBS_LCD_I2C.h"
#include "C_JBS_LedNeoPixel.h"
#include "C_JBS_FillingSystem.h"

//Beginning of Auto generated function prototypes by Atmel Studio
unsigned int SetBotlleFull(unsigned int machineMode, bool& bBottleEmpty_1, bool& bBottleEmpty_2, bool& bBottleEmpty_3, bool& bBottleEmpty_4);
unsigned int CheckBotlleReady(unsigned int machineMode, bool& bBottleEmpty_1, bool& bBottleEmpty_2, bool& bBottleEmpty_3, bool& bBottleEmpty_4);
//End of Auto generated function prototypes by Atmel Studio




// define two tasks for Blink & AnalogRead
void TaskFilling( void *pvParameters );
void TaskMonitoring( void *pvParameters );
void TaskMenuHandling( void *pvParameters );

/* Global Variable */

// Program variable
unsigned int gmachineState=0;
// 0 Wait for bottle
// 1 Filling ready
// 2 Filling
// 3 Remove bottle
 
uint8_t gu8_Mode{0u};

// 0 UserChoice
// 1 Manual
// 2 Semi Auto
// 3 Auto
// 4 Cleaning

unsigned int gMachineMode=1;   // number of used valve
unsigned int gu32TimingFilling=20; // 20 ms cycle time

C_JBS_LCD_I2C g_Lcd;//(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
C_JBS_LedNeoPixel g_Leds;
C_JBS_FillingSystem g_FillingSystem;
// the setup function runs once when you press reset or power the board
void setup() {
  
    g_Lcd.Init();                      // initialize the LCD
    //g_Lcd.write(8u);
    g_Lcd.ClearPrint(g_Lcd.MAC8_INIT);
    //g_Lcd.write(8u);
  
    g_Leds.init();
    g_Leds.setPixelColor(0, g_Leds.Color(255u, 0u, 0u));
    g_Leds.show();   // Send the updated pixel colors to the hardware.

    pinMode(AU8_PIN_CT[0], INPUT_PULLUP);
    //pinMode(AU8_PIN_CT[1], INPUT_PULLUP);
    //pinMode(AU8_PIN_CT[2], INPUT_PULLUP);
    //pinMode(AU8_PIN_CT[3], INPUT_PULLUP);

  pinMode(U8_JBS_LED_NEO_PIXEL_DATA_PIN, OUTPUT);
  //pinMode(U8_PIN_SI_LED_2, OUTPUT);
  //pinMode(U8_PIN_SI_LED_3, OUTPUT);
  //pinMode(U8_PIN_SI_LED_4, OUTPUT);
  
  pinMode(AU8_PIN_BT_CAL[0], INPUT_PULLUP);
  //pinMode(U8_PIN_BT_CAL_2, INPUT_PULLUP);
  //pinMode(U8_PIN_BT_CAL_3, INPUT_PULLUP);
  //pinMode(U8_PIN_BT_CAL_4, INPUT_PULLUP);
  
  //pinMode(PIN_BtMain, INPUT_PULLUP);
  
  pinMode(AU8_PIN_V[0], OUTPUT);
  //pinMode(U8_PIN_V_2, OUTPUT);
  //pinMode(U8_PIN_V_3, OUTPUT);
  //pinMode(U8_PIN_V_4, OUTPUT);
  
  digitalWrite(AU8_PIN_V[0], 0);
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
    }

    Serial.println("Program start:");

  // Now set up two tasks to run independently.
    xTaskCreate(
    TaskMenuHandling
    ,  "Menu Handling"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack High water
    ,  NULL
    ,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  //xTaskCreate(
    //TaskFilling
    //,  /*(const portCHAR *)*/"Fill"   // A name just for humans
    //,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    //,  NULL
    //,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    //,  NULL );

  xTaskCreate(
    TaskMonitoring
    ,  /*(const portCHAR *)*/ "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
    
void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskMenuHandling(void *pvParameters)  // This is a task.
{
    g_Lcd.PrintInit();
    g_FillingSystem.Init(U8_PIN_BT_PEDALE, AU8_PIN_V, AU8_PIN_BT_CAL, AU8_PIN_CT, &g_Leds);
    uint8_t Last_Mode{0xff};    

    for (;;)
    {
        g_FillingSystem.UpdateInput();
        
        if (Last_Mode!=gu8_Mode)
        {
            switch(gu8_Mode)
            {
                case 0:
                g_Lcd.ClearPrint(g_Lcd.MAC8_MODE_CHOOSE);
                
                break;

                default:
                ;
            }
           Last_Mode = gu8_Mode;
        }
        if (gu8_Mode == 0u)
        {
            if(g_FillingSystem.GetBtCalPressed(1u))
            {
                gu8_Mode = 1;
            }
            else if(g_FillingSystem.GetBtCalPressed(2u))
            {
                gu8_Mode = 2;
            }
        
            else if(g_FillingSystem.GetBtCalPressed(3u))
            {
                gu8_Mode = 3;
            }
            else if(g_FillingSystem.GetBtCalPressed(4u))
            {
                gu8_Mode = 4;
            }
        }
        vTaskDelay( 100u / portTICK_PERIOD_MS ); // wait for one second
    }
}

//void TaskFilling(void *pvParameters)  // This is a task.
//{
  //(void) pvParameters;
  //bool bBtCal_1=1;
  //bool bBtCalLast_1=1;
//
  //bool bBottleEmpty_1=1;
  //bool bBottleEmpty_2=1;
  //bool bBottleEmpty_3=1;
  //bool bBottleEmpty_4=1;
  //
  //bool bValve=0;
  //bool bFilling=0;
  //unsigned int u32ctClick=0;
  //unsigned int u32ctValve=0; 
  //unsigned int u32FillingTimeCal=0;
  //unsigned int u32FillingTime=0;
  //
  //unsigned int NumberFilledBottle=0;
  //
  //
  //for (;;) // A Task shall never return or exit.
  //{
    //
    //bBtCal_1=digitalRead(U8_PIN_BT_CAL_1);
    //
    //if (CheckBotlleReady(gMachineMode, bBottleEmpty_1, bBottleEmpty_2, bBottleEmpty_3, bBottleEmpty_4))
    //{
      //if (bBtCal_1==0 and bBtCalLast_1==1)
      //{
        //u32FillingTime=u32FillingTimeCal-(NumberFilledBottle/5*1);
        //bFilling=1;
        //u32ctClick=0;
      //}
      //else if (bBtCal_1==0)
      //{
        //u32ctClick++;
      //}
      //else if (u32ctClick > 3000/gu32TimingFilling and bBtCalLast_1==0 and bBtCal_1==1)
      //{
        //bFilling=0;
        //u32FillingTimeCal=u32ctClick;
        //Serial.print("Saved filling Time: ");
        //Serial.println(u32FillingTimeCal*gu32TimingFilling);
      //}
    //}
    //
      ////Serial.print("Filling state: ");
      ////Serial.println(bFilling);
    //if (bFilling)
    //{
      //u32ctValve++;
      //bValve=1;
//
      //if (u32ctValve>=u32FillingTime and bBtCal_1==1)
      //{ 
        ////Serial.println("Valve Closed ");
        //u32ctValve=0;
        //bFilling=0;
        //bValve=1;
        //
        //SetBotlleFull(gMachineMode, bBottleEmpty_1, bBottleEmpty_2, bBottleEmpty_3, bBottleEmpty_4);
        //NumberFilledBottle+=gMachineMode;
        //Serial.print("Number of filled bottles: ");
        //Serial.println(NumberFilledBottle);
      //}
    //}
    //else
    //{
      //bValve=0;
    //}
    //digitalWrite(U8_PIN_V_1, bValve);
    //bBtCalLast_1=bBtCal_1;
    //vTaskDelay( gu32TimingFilling / portTICK_PERIOD_MS ); // wait for one second
  //}
//}
//
//unsigned int SetBotlleFull(unsigned int machineMode, bool& bBottleEmpty_1, bool& bBottleEmpty_2, bool& bBottleEmpty_3, bool& bBottleEmpty_4)
//{
  //bBottleEmpty_1&=machineMode<1;
  //bBottleEmpty_2&=machineMode<2;
  //bBottleEmpty_3&=machineMode<3;
  //bBottleEmpty_4&=machineMode<4;
//}
//
//unsigned int CheckBotlleReady(unsigned int machineMode, bool& bBottleEmpty_1, bool& bBottleEmpty_2, bool& bBottleEmpty_3, bool& bBottleEmpty_4)
//{
  //bBottleEmpty_1|=digitalRead(AU8_PIN_CT[0]);
  //bBottleEmpty_2|=digitalRead(AU8_PIN_CT[1]);
  //bBottleEmpty_3|=digitalRead(AU8_PIN_CT[2]);
  //bBottleEmpty_4|=digitalRead(AU8_PIN_CT[3]);
    //
  //switch(machineMode)
  //{
    //case 1:
    //return !digitalRead(AU8_PIN_CT[0]) && bBottleEmpty_1;
    //break;
    //
    //case 2:
    //return !digitalRead(AU8_PIN_CT[0])&&!digitalRead(AU8_PIN_CT[1]) && !digitalRead(AU8_PIN_CT[0])&&!digitalRead(AU8_PIN_CT[1]);
    //break;
    //
    //case 3:
    //return digitalRead(AU8_PIN_CT[0])&&digitalRead(AU8_PIN_CT[1])&&digitalRead(AU8_PIN_CT[2]) && !digitalRead(AU8_PIN_CT[0])&&!digitalRead(AU8_PIN_CT[1])&&!digitalRead(AU8_PIN_CT[2]);
    //break;
    //
    //case 4:
    //return digitalRead(AU8_PIN_CT[0])&&digitalRead(AU8_PIN_CT[1])&&digitalRead(AU8_PIN_CT[2])&&digitalRead(AU8_PIN_CT[3]) && !digitalRead(AU8_PIN_CT[0])&&!digitalRead(AU8_PIN_CT[1])&&!digitalRead(AU8_PIN_CT[2])&& !digitalRead(AU8_PIN_CT[3]);
    //break;
  //}
//}


void TaskMonitoring(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // print out the value you read:
    //Serial.println(sensorValue);
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
  }
}

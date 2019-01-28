/****************************************************************
 *
 *                The MIT License
 *
 *   Copyright (c) 2017-2018  tomoaki@tomy-tech.com
 *   modified by himitu23 (@_tokina23)
 *
 ***************************************************************/
#include <KashiwaGeeks.h>
#include <Wire.h>

#define ECHO true

ADB922S LoRa;

//================================
//          Initialize Device Function
//================================
#define BPS_9600       9600
#define BPS_19200     19200
#define BPS_57600     57600
#define BPS_115200   115200

void start()
{
    /*  Setup console */
    ConsoleBegin(BPS_57600);
    ConsolePrint(F("\n**** I2C_Temp_Sensor_Sample (only get the temp data) *****\n"));

    Wire.begin();
}


//========================================
// Functions to be executed periodically
//========================================
void taskTemp(void)
{
    getTemp();
}
//========================================
//            Execution interval
//    TASK( function, initial offset, interval by minute )
//========================================
TASK_LIST = {
        TASK(taskTemp, 0, 1),
        END_OF_TASK_LIST
};

//================================
//          Power save functions
//================================
void sleep(void)
{
    LoRa.sleep();
    DebugPrint(F("Sleep.\n"));
}
void wakeup(void)
{
    LoRa.wakeup();
    DebugPrint(F("Wakeup.\n"));
}


//================================
// I2C ADT7410 Sensor Functions
//================================
void getTemp(void)
{
  Wire.requestFrom(0x48,2);
  uint16_t val = Wire.read() << 8;
  val |= Wire.read();
  val >>= 3;    // convert to 13bit format
  int ival = (int)val;//for 16bit
  if ( val & (0x8000 >> 3) )
  {
    ival -= 8192;
  }
  float temp = (float)ival / 16.0;
  char buf[6];
  DebugPrint(F("Temp=%s [C]\n"), dtostrf(temp,3, 2, buf));

}
/*   End of Program  */

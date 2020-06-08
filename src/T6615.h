/*  6/2020 by Fernando Muller da Silva - Intituto Federal de Santa Catarina-IFSC
            Arduino Uno Software Serial example with CO2 Sensor Telaire T6615 0-10k PPM
            Functions:
               warmup();
               skipWarmup();
               halt();
               testSTART();
               testRESULTS();
               idleON();
               idleOFF();
               readPPM();
               readSTATUS();
               readELEVATION();
               readABC();
               readSGPT();
               setSGPT(int p);
               sgptCALIBRATE(); 

             Telaire T6615 Specifications and Product Documents:
             https://www.amphenol-sensors.com/en/telaire/co2/525-co2-sensor-modules/319-t6615 

*/

#ifndef __TELAIRE_T6615_ARDUINO_LIBRARY_H__
#define __TELAIRE_T6615_ARDUINO_LIBRARY_H__

#include "Arduino.h"
#include "SoftwareSerial.h"

#define FLAG          0xFF
#define ADDR          0xFE

#define CMD_WARM      0x84
#define CMD_SKIP_WARMUP 0x91
#define CMD_HALT      0x95
#define CMD_READ      0X02
#define SERIAL_NUMBER 0x01
#define CO2PPM        0x03
#define ELEVATION     0x0F

#define STATUS        0xB6

#define CMD_SGPT_CALIBRATE 0x9B
#define CMD_SET       0X03
#define CMD_VFY       0x02
#define SGPTPPM       0X11

#define CMD_ABC       0xB7
#define ABC_VFY       0x00
#define ABC_ON        0x01
#define ABC_RESET     0x03
#define ABC_OFF       0x02

class T66
{
public:
  T66(void);
    void begin(SoftwareSerial &serialPort); 
    
    byte response[7] = {0,0,0,0,0,0,0}; 

    void warmup();
    void skipWarmup();
    void halt();
    void testSTART();
    void testRESULTS();
    void idleON();
    void idleOFF();
    void readPPM();
    void readSTATUS();
    void readELEVATION();
    void readABC();
    void readSGPT();
    void setSGPT(int p);
    void sgptCALIBRATE();
    void sendRequest(byte packet[],int arrayLen, int respLen);

    unsigned long getPPMorSGPT(byte packet[]);
    unsigned long getElevation(byte packet[]);
  

private:
  SoftwareSerial *T66_Serial; 
};
#endif

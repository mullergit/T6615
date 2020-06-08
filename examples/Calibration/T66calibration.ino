/*   2/2017 by Marv kausch @ Co2meter.com
            AN-157 Demo of T-66 using Software Serial
            Arduino example for t6613 CO2 sensor 0-2000 PPM   19200 BPS
            
     6/2020 by Fernando Muller da Silva - Intituto Federal de Santa Catarina-IFSC
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

             Wiring diagram below for the Arduino Uno or Arduino Mega
             http://co2meters.com/Documentation/AppNotes/AN157-T6613-Arduino-uart.pdf
*/
#include "T6615.h"

//Using Arduino Uno pin 12 for Rx and pin 13 for Tx
SoftwareSerial softSerial(12,13); //Sets up a virtual serial port

T66 sensor;

bool flagCalibration = true;

void setup(){
  
   Serial.begin(19200); //Opens the main serial port to communicate with the computer
   sensor.begin(softSerial); //Opens the virtual serial port with a baud of 9600
   Serial.println("\n\t Arduino Uno Software Serial and T6615 CO2 sensor \n"); 
   
}

void loop(){  
    
   if(flagCalibration){  
       Serial.print("\n readSTATUS()...");
       sensor.readSTATUS();

       if(sensor.response[3]==0){
           Serial.print("\n Sensor OK. Starting calibration...");
           
           Serial.print("\n readPPM()");
           sensor.readPPM();
      
           Serial.print("\n readSGPT()");
           sensor.readSGPT();
           delay(1000);
           
           //Set the CO2 concentration reference. 
           //Use another co2 sensor reading as a reference and change the value
           Serial.print("\n setSGPT()");
           sensor.setSGPT(713);//Set CO2 concentration in 874 ppm reference
           delay(1000);
           
           Serial.print("\n readSGPT()");
           sensor.readSGPT();
           delay(1000);
           
           Serial.print("\n readSTATUS()");
           sensor.readSTATUS();
           delay(1000);
           
           Serial.print("\n SGPT_CALIBRATE()");
           sensor.sgptCALIBRATE();
           delay(1000);

           flagCalibration=false;
       }                    
   }

   sensor.readSTATUS();
   
   if(sensor.response[3]==4){
      Serial.print("\n Calibrating sensor. Wait...");
   } 
   
   if(sensor.response[3]==0){
      Serial.print("\n readPPM()");
      sensor.readPPM();
   }
   
   delay(20000);
   
}

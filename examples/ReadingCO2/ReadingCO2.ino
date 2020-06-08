/*   6/2020 by Fernando Muller da Silva - Intituto Federal de Santa Catarina-IFSC
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
#include "T6615.h"

//Using Arduino Uno pin 12 for Rx and pin 13 for Tx
SoftwareSerial softSerial(12,13); //Sets up a virtual serial port

T66 sensor;

void setup(){
  
   Serial.begin(19200); //Opens the main serial port to communicate with the computer
   sensor.begin(softSerial); //Opens the virtual serial port with a baud of 9600
   Serial.println("\n\t Arduino Uno Software Serial and T6615 CO2 sensor \n"); 
   
}

void loop(){      
   

   Serial.print("\n readSTATUS()...");
   sensor.readSTATUS();
   
   if(sensor.response[3]==0){
      Serial.print("\n readPPM()");
      sensor.readPPM();
   }
   
   delay(10000);
   
}
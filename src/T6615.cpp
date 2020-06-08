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

T66::T66(void){
  
}
void T66::begin(SoftwareSerial &SerialPort){
  T66_Serial = &SerialPort;
  T66_Serial->begin(19200);   
}
void T66::warmup(){
  byte pct[] = {FLAG, ADDR, 0x01, CMD_WARM};
  sendRequest(pct,4,3);
}
void T66::skipWarmup(){
  byte pct[] = {FLAG, ADDR, 0x01, CMD_SKIP_WARMUP};
  sendRequest(pct,4,3);
}
void T66::halt(){
  byte pct[] = {FLAG, ADDR, 0x01, CMD_HALT};
  sendRequest(pct,4,3);
}
void T66::idleON(){
  byte pct[] = {FLAG, ADDR, 0x05, 0xB9, 0x01};
  sendRequest(pct,5,3);
}
void T66::testSTART(){
  byte pct[] = {FLAG, ADDR, 0x05, 0xC0, 0x00};
  sendRequest(pct,5,3);
}
void T66::testRESULTS(){
  byte pct[] = {FLAG, ADDR, 0x05, 0xC0, 0x01};
  sendRequest(pct,5,7);
}
void T66::idleOFF(){
  byte pct[] = {FLAG, ADDR, 0x05, 0xB9, 0x02};
  sendRequest(pct,5,3);
}
void T66::readPPM(){
   byte pct[]= {FLAG, ADDR, 0x02, CMD_READ, CO2PPM};
   sendRequest(pct,5,5);
   Serial.print("    Co2 ppm = ");Serial.println(getPPMorSGPT(response));
}
void T66::readSTATUS(){
  byte pct[] = {FLAG, ADDR, 0x01, STATUS};
  sendRequest(pct,4,4);
}
void T66::readELEVATION(){
   byte pct[]= {FLAG, ADDR, 0x02, CMD_READ, ELEVATION};
   sendRequest(pct,5,5);   
   Serial.print("    Elevation = ");Serial.println(getElevation(response));
}
void T66::readABC(){
   byte pct[]= {FLAG, ADDR, 0x02, CMD_ABC, ABC_VFY};
   sendRequest(pct,5,4);
}
void T66::readSGPT(){
   byte pct[]= {FLAG, ADDR, 0x02, CMD_VFY, SGPTPPM};
   sendRequest(pct,5,5);
   Serial.print("    SGPT ppm = ");Serial.println(getPPMorSGPT(response));
}
void T66::setSGPT(int p){
  union {
    int16_t dec;
    byte buf[2];
  }ppm;
  ppm.dec=p;
  byte pct[] = {FLAG, ADDR, 0x04, CMD_SET, SGPTPPM, ppm.buf[1], ppm.buf[0]};
  sendRequest(pct,7,3);
}
void T66::sgptCALIBRATE(){
  byte pct[] = {FLAG, ADDR, 0x01, CMD_SGPT_CALIBRATE};
  sendRequest(pct,4,3);
}
void T66::sendRequest(byte packet[],int arrayLen, int respLen){  
   while(!T66_Serial->available()){ 
     T66_Serial->write(packet,arrayLen);
     delay(50);
     delay(1000);
   }
   int timeout=0; 
   while(T66_Serial->available() < respLen){  
     timeout++;
     if(timeout > 10) 
     Serial.print("Timeout");
     {
     while(T66_Serial->available()) 
     T66_Serial->read();
         
     break; 
     }
     delay(50);
   }
  for (int i=0; i < respLen; i++) response[i] = T66_Serial->read();
  Serial.print("\t Sensor response:   ");
   for(int i=0;i<respLen;i++){
    Serial.print(response[i],HEX);
    Serial.print(" ");
   }
}

unsigned long T66::getPPMorSGPT(byte packet[]){
   int high = packet[3]; 
   int low = packet[4]; 
   unsigned long val = high*256 + low; 
   return val;
}
unsigned long T66::getElevation(byte packet[]){  
   int high = packet[4]; 
   int low = packet[3]; 
   unsigned long val = high*256 + low; 
   return val;
}

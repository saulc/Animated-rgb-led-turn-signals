
#include "Arduino.h"
#include "PwmRead.h"

pwmRead::pwmRead(int p){
    pin = p;
    pinMode(p, INPUT);
    ini();
}

pwmRead::pwmRead(int p, int n){
    pin = p;
    neutral = n;
    //pinMode(p, INPUT);
    ini();
}
void pwmRead::ini(){
   // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
pwmRead::~pwmRead(){
}

int pwmRead::getDir(){
    int ms = getPulseWidth();
    int dx = neu; //neutral/dead zone
    
    int r = 0;
    if(ms > (neutral + dx) ){ 
        r = 1;  //fwrd     
    }else if(ms < (neutral - dx) ){
        r = -1;  // rev
    } else if(ms == 0)
      r = 0;  //neutral
      
    
    return r;
}
  
int pwmRead::getPulseWidth(){
        //analog smoothing
        // subtract the last reading:
        total = total - readings[readIndex];
        
        int ms = pulseIn(pin, HIGH, 20000);
        // read from the sensor:
        readings[readIndex] = ms;
        // add the reading to the total:
        total = total + readings[readIndex];
        // advance to the next position in the array:
        readIndex = readIndex + 1;
      
        // if we're at the end of the array...
        if (readIndex >= numReadings) {
          // ...wrap around to the beginning:
          readIndex = 0;
        }
      
        // calculate the average:
        average = total / numReadings;
  
        if(average > 0){
              lastPulse = micros();
              return ms;
                
            }
            else if(lastPulse - micros() > timeOut){
              //fallback, if no pwn signal or pulses
                return neutral;
               
            }
            
        return average;
   }
            
    
   

int pwmRead::getNeutral(){
    return neutral;
}

void pwmRead::setNeutral(int n){
    neutral = n;
}

int pwmRead::getNeu(){
    return neu;
}

void pwmRead::setNeu(int n){
    neu = n;
}
   


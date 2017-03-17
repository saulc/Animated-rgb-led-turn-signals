
#include "PwmRead.h"
#include "rgb.h"

/*
 * Saul Castro
 * Created 12/16
 * updated 3/17
 * 
 * Software for animated rgb led tail light for rc cars/trucks/skateboards/robots.
 * More information on the complete project can be found at
 * https://hackaday.io/project/20364-animated-led-braketurn-signal
 * 
 * This version uses an ws2812 x8 led module with 1 led burned out.
 */

 /*
  * Copyright [2017] [Saul Castro]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
    
        http://www.apache.org/licenses/LICENSE-2.0
    
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

  */
//digital/interupt pins for sampling pwm ch1/2 of rc style rx
int tin = 2; // for throtttle input/passthrough
int lin =  1;     //for light/turn signal input

//pwm pin for rgb leds
int ll = 0; //rgb ws2801 leds

//mostfet 500ma for led headlights.
//probably too much for vesc/drv 5v 1A max 
//int l0 = 0; 
//int l1 = 1;

pwmRead tpin = pwmRead(tin, 1660);
pwmRead lpin = pwmRead(lin, 1660);
// todo 
/*  Auto detect neutral/min/max
 *    set deadzone by input sequence
 * 
 */
//wrapped ada lib for module code
rgb leds = rgb(ll, 7, 0); 

void setup() {
//debuging serial for nano //uncomment print functions at bottom
//  Serial.begin(9600);
//  pl("Tiny rc led turnsignal test");
//  pl(leds.getN());
     leds.ini();
  wakeUp();
  leds.bounce(3, 10);
  delay(1000);
      tpin.setNeu(120); //let the brake lights be trigger easier than turn signals
    leds.setMode(6, 10);
    delay(1500);
     // demo();
}
int val = 0;
int timer = 1000/50*3; //sleep timer
int tt = 0;
int alt = 0;

void loop() {

      //read throttle and steering input pins
      int th = tpin.getDir();
      delay(10); // won't read next signal without 
      int st = lpin.getDir();
//      pt("th: ");
//      pt(th);
//      pt(" st: ");
//      pl(st);

      //figure out what to do
      int m = 1;    //default rest mode   
      if(th == -1)  m = 6;    //brake, overrides turn signals for now. better for saftey?
      else if(st == 1) m = 9; //left seqence
      else if(st == -1) m = 10; //right seqence

      //do it. (said even stenvens guy)
      if(m != val){
        leds.setMode(m, 10);
        val = m;
        delay(200);
      }
      delay(50);  //read about 20x/sec 
    
    //alternate timed sequence or mode 
    if((tt++ > timer) && m!=6) {
      if(alt) 
        leds.bounce(3, 10);
      else
        wakeUp();
        
      tt = 0;
      alt = !alt;
    }else if(m==6){
        delay(300);   //hold the brake animation for visibilty/saftey
      
    }
      //repeat for - ev - er!
}
//start/wake sequence
void wakeUp(){
       for(int i=0; i<4; i++){
        leds.silon(1, 10 + 3*i);  //center out
        delay(200);
        leds.rilon(1, 10 + 5*i);  //out in
        delay(200);
       // leds.bounce(3-i, 10-i);
      }
}
// simple demo to show/test sequences/blinkers
void demo(){
    leds.setMode(7, 10);
    delay(1000);
    leds.setMode(1, 10);
    delay(1000);
    leds.setMode(8, 10);
    delay(1000);
    leds.setMode(1, 10);
    delay(1000);

     leds.setMode(9, 10);
  
    delay(1000);
    leds.setMode(1, 10);
    delay(1000);
    leds.setMode(10, 10);

    delay(1000);
    leds.setMode(6, 10);
    delay(1000);
}

//void printPulseWidth(){
//  
//        int tt = tpin.getPulseWidth();
//        delay(8); // won't read next signal without 
//        int ss = lpin.getPulseWidth();
//       pt("pwt:");
//       pt(tt);
//       pt(" sw: ");
//       pl(ss);          
//}
//void pt(String s){
//  
//  Serial.print(s);
//}
//void pl(String s){
//  
//  Serial.println(s);
//}
//
//void pt(int s){
//  
//  Serial.print(s);
//}
//void pl(int s){
//  
//  Serial.println(s);
//}




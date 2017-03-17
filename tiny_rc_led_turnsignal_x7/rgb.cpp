
#include "rgb.h"


 rgb::rgb(int Pin){
    n = 10;
    p = Pin;
    s = 0;  //no status leds, only tail lights
 }
 
 rgb::rgb(int Pin, int N, int S){
    p = Pin;
    n = N + S;
    s = S;
    
 }
     
rgb::~rgb(){

}

     
int rgb::arrayLength(uint32_t *a){
  int size = sizeof(a) / sizeof(uint32_t);
  
  return size;
}

void rgb::blinkLeft(){
  for(int i=0; i<turnFlashes; i++){
      rest(turnDelay);
      pixels.setPixelColor(s+ 5, leftColor);
      pixels.setPixelColor(s+ 6, leftColor);  
      pixels.show();
      delay(turnDelay);
  }
  rest(10);
}
void rgb::blinkRight(){
  for(int i=0; i<turnFlashes; i++){
      rest(turnDelay);
      pixels.setPixelColor(s+ 0, rightColor);
      pixels.setPixelColor(s+ 1, rightColor);
      pixels.show();
      delay(turnDelay);
  }
  rest(10);
}

void rgb::bounce(int a, int d){
  uint32_t c = sColor;
  for(int i=0; i<a; i++){
    
  
  for(int i=0; i<n; i++){
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(d);
      rest(d);
      }
      for(int i=n; i>=0; i--){
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(d);
      rest(d);
      }
  }
  
}

void rgb::silon(int a, int d){
   //uint32_t c = brakeColor;
   uint32_t c = sColor;
  for(int i=0; i<a; i++) 
     for(int i=0; i<n/2; i++) {
     
      pixels.setPixelColor(s+ n/2+i, c);
      pixels.setPixelColor(s+ n/2-i, c);
      pixels.show();
      delay(d);
     rest(d);    
     }
}


void rgb::rilon(int a, int d){
     uint32_t c = sColor;
  for(int i=0; i<a; i++) 
     for(int i=n/2; i>0; i--) {
     
      pixels.setPixelColor(s+ n/2+i, c);
      pixels.setPixelColor(s+ n/2-i, c);
      pixels.show();
      delay(d);
     rest(d);    
     }
}

void rgb::turnLeft(){
  blinkLeft();
      uint32_t c = brakeColor;
     for(int i=0; i<turnFlashes; i++) {
     
     pixels.setPixelColor(s+ 3, c);
      pixels.show();
      delay(turnDelay);
      
      pixels.setPixelColor(s+ 4, c);
      pixels.show();
      delay(turnDelay);
    
      pixels.setPixelColor(s+ 5, c);
      pixels.show();
      delay(turnDelay);

      pixels.setPixelColor(s+ 6, c);
      pixels.show();
      delay(turnDelay);

      rest(50);
  }
}

void rgb::turnRight(){
  blinkRight();
  uint32_t c = brakeColor;
  
  for(int i=0; i<turnFlashes; i++) {
      
      pixels.setPixelColor(s+ 3, c);
      pixels.show();
      delay(turnDelay);
      
      pixels.setPixelColor(s+ 2, c);
      pixels.show();
      delay(turnDelay);
    
      pixels.setPixelColor(s+ 1, c);
      pixels.show();
      delay(turnDelay);

      pixels.setPixelColor(s+ 0, c);
      pixels.show();
      delay(turnDelay);
      
      rest(50);
  }
}

void rgb::brake(){
  for(int a =0; a<brakeFlashes; a++){
    //rest(50);
    rilon(1, 15);
    silon(1, 15);
    delay(10);
  }
    for(uint32_t i=s; i<n; i++) {
       
         pixels.setPixelColor(i,  brakeColor);
         pixels.show();
      delay(10);
    }
    delay(brakeDelay);   
  
}

void rgb::rest(int d){
 

    colorWipe(restColor, 10);
    delay(d);
  
}
void rgb::ini(){
    pixels = Adafruit_NeoPixel(n, p, NEO_GRB + NEO_KHZ800);
    delay(50);
    pixels.begin();
    pixels.show(); // Initialize all pixels to 'off'
    pixels.setBrightness(50);
}

void  rgb::setN(int N){
  n = N;
}

int  rgb::getN(){
  return n;
}

void  rgb::setMode(int M, int d){
      if(M == mode){
        delay(50);
        return;
      }
      
      mode = M;
        switch(mode){
    case 0: colorWipe(pixels.Color(0, 0, 0), d);    // Black/off
            break;
    case 1: colorWipe(restColor, d);  // Red
            break;
    case 2: colorWipe(pixels.Color(0, 255, 0), d);  // Green
            break;
    case 3: colorWipe(pixels.Color(0, 0, 55), d);  // Blue
            break;
    case 4: colorWipe(pixels.Color(255, 100, 0), d); //left
            break;
    case 5: acolorWipe(pixels.Color(0, 255, 50), d); //right
                break;
    case 6: brake();
            break;
    case 7: blinkLeft();
            break;
    case 8: blinkRight();
            break; 
    case 9: turnLeft();
            break;
    case 10: turnRight();
            break;                     
    default:   rest(50);  // Red         
    }       
}

void  rgb::nextMode(){
    mode = ++mode >= modes ? 0 : mode;
}
void  rgb::prevMode(){
    mode = --mode < 0 ? modes-1 : mode;
}
int  rgb::getMode(){
  return mode;
}


    
// Fill the dots one after the other with a color
void rgb::colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<n; i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
  }
}

 void rgb::acolorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=n-1; i>=0; i--) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
  }
}

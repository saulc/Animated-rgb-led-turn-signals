
#ifndef Rgb_h
#define Rgb_h

/*
 * Neo pixel wrapper class for modular animation/color control
 * 
 */
#include <Adafruit_NeoPixel.h>
#include "SystemStatus.h"


class rgb{
  public:
    rgb(int Pin);
    rgb(int Pin, int N, int S);
    rgb(int Pin, int N, uint32_t* m, uint32_t* u, uint32_t* l, uint32_t* r, uint32_t* t);
    ~rgb();

    void ini();
    void setN(int N);
    int getN();
    void setMode(int M, int d);
    void nextMode();
    void prevMode();
    int getMode();
    void colorWipe(uint32_t c, uint8_t wait); 
    void acolorWipe(uint32_t c, uint8_t wait); 
    int arrayLength(uint32_t *a);

    void turnLeft();
    void turnRight();
    void blinkLeft();
    void blinkRight();
    void brake();
    void rest(int d);
    void rilon(int n, int d);
    void silon(int n, int d);
    void bounce(int n, int d);
    
    private:
      int p, n, s;  //pin, how many, howmany  for status
      uint32_t *main, *under, *left, *right, *tail;
      int mode, modes = 6, turnDelay = 200, turnFlashes = 4,
      brakeFlashes = 2, brakeDelay= 100;
      uint32_t brakeColor = pixels.Color(255, 0, 0);
      uint32_t rightColor = pixels.Color(210, 0, 0);
      uint32_t leftColor = pixels.Color(210, 0, 0);
      uint32_t restColor = pixels.Color(80, 0, 0);
      uint32_t sColor = pixels.Color(250, 250, 0);
      Adafruit_NeoPixel pixels; 
};

#endif













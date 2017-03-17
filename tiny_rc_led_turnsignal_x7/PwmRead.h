
#ifndef PwmRead_h
#define PwmRead_h
/*
 * Saul Castro
 * 
 * analog smoothing adapted for reading a pwm from rc rx
 * using pulseIn();
 * integrated deadzone from center point
 */



class pwmRead{

  public:
  pwmRead(int p);
  pwmRead(int p, int n);
  ~pwmRead();


      int getPulseWidth(); //returns pulse in micros
      int getDir(); //return direction of signal forward/rev
      int getNeutral();
      void setNeutral(int n);
      int getNeu();
      void setNeu(int n);
      void ini();

  private:
    int pin;
    long timeOut = 10000, lastPulse = 0;
    int neu = 200;
    int neutral = 1500;

    //analog smoothing 
    static const int numReadings = 10;    
    int readings[numReadings];      // the readings from the analog input
    int readIndex = 0;              // the index of the current reading
    int total = 0;                  // the running total
    int average = 0;                // the average
  
};

#endif








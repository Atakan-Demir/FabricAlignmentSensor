#ifndef Entegre_h
#define Entegre_h

#include "Arduino.h"

class Entegre {
private:
  const int muxChannel[16][4] = {
      
      { 0, 0, 0, 0 },  
      { 1, 0, 0, 0 },  
      { 0, 1, 0, 0 }, 
      { 1, 1, 0, 0 },  
      { 0, 0, 1, 0 },  
      { 1, 0, 1, 0 },  
      { 0, 1, 1, 0 },  
      { 1, 1, 1, 0 },  
      { 0, 0, 0, 1 },  
      { 1, 0, 0, 1 },  
      { 0, 1, 0, 1 },  
      { 1, 1, 0, 1 },  
      { 0, 0, 1, 1 },  
      { 1, 0, 1, 1 },  
      { 0, 1, 1, 1 },  
      { 1, 1, 1, 1 }   
    };
  int controlPin[4];
  int SIG_pin;
  int enablePin;
  

public:
  int openDoor;
  Entegre(int s0, int s1, int s2, int s3, int sig, int enable);
  void activate();
  void deactivate();
  void setChannel(int channel);
  int read();
};

class EntegreYonetici {
private:
  Entegre* entegreler;
  int entegreSayisi;

public:
  EntegreYonetici(Entegre* entegreDizisi, int sayisi);
  int readMux(int entegreIndex, int channel);
  int rightLeftCheck(int entegreIndex);
  int rightCount();
  int leftCount();
  int average(int offset);
};

#endif

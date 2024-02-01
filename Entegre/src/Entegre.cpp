#include "Entegre.h"

// Entegre sınıfı fonksiyonlarının implementasyonları
Entegre::Entegre(int s0, int s1, int s2, int s3, int sig, int enable) : enablePin(enable) {

    // Kontrol pinlerini ve sinyal pinini atanir
    controlPin[0] = s0;
    controlPin[1] = s1;
    controlPin[2] = s2;
    controlPin[3] = s3;
    SIG_pin = sig;
    openDoor = 0;

    // Kontrol pinlerini cikis olarak ayarla ve yuksek duruma getir
    for (int i = 0; i < 4; i++) {
      pinMode(controlPin[i], OUTPUT);
      digitalWrite(controlPin[i], HIGH);
    }

    // Etkinlestirme pinini cikis olarak ayarla ve devre disi birak
    pinMode(enablePin, OUTPUT);
    deactivate();
}

void Entegre::activate() {
   digitalWrite(enablePin, LOW);
}

void Entegre::deactivate() {
    digitalWrite(enablePin, HIGH);
}

void Entegre::setChannel(int channel) {
   for (int i = 0; i < 4; i++) {
      digitalWrite(controlPin[i], muxChannel[channel][i]);
    }
}

int Entegre::read() {
    return digitalRead(SIG_pin);
}

// EntegreYonetici sınıfı fonksiyonlarının implementasyonları
EntegreYonetici::EntegreYonetici(Entegre* entegreDizisi, int sayisi)
  : entegreler(entegreDizisi), entegreSayisi(sayisi) {}

int EntegreYonetici::readMux(int entegreIndex, int channel) {
    // Tum entegreleri devre disi birak
    for (int i = 0; i < entegreSayisi; i++) {
      entegreler[i].deactivate();
    }
    // Istenen entegreyi aktif et
    entegreler[entegreIndex].activate();
    // Istenen kanali ayarla
    entegreler[entegreIndex].setChannel(channel);
    // Degeri oku
    int val = entegreler[entegreIndex].read();


    // entegrenin kanalı açık mı kapalımı döndür
    if (val == 1) {
      return 1;
    } else {
      return 0;
    }



    // Islem bittikten sonra entegreyi devre disi birak
    entegreler[entegreIndex].deactivate();
}

int EntegreYonetici::rightLeftCheck(int entegreIndex) {
    if (entegreIndex < entegreSayisi / 2) {
      return 1;
    } else {
      return 0;
    }
}

int EntegreYonetici::rightCount() {
    int count = 0;
    for (int i = 0; i < entegreSayisi; i++){
      int cup = rightLeftCheck(i);
      if(cup==1){
        count+= entegreler[i].openDoor;
      }
    }
    return count;
}

int EntegreYonetici::leftCount() {
    int count = 0;
    for (int i = 0; i < entegreSayisi; i++){
      int cup = rightLeftCheck(i);
      if(cup==0){
        count+= entegreler[i].openDoor;
      }
    }
    return count;
}

int EntegreYonetici::average(int offset) {
   int avg = offset;
    for (int entegreIndex = 0; entegreIndex < entegreSayisi; entegreIndex++) {
      if(rightLeftCheck(entegreIndex)==1){
        avg += entegreler[entegreIndex].openDoor;
      } else {
        avg += entegreler[entegreIndex].openDoor * -1;
      }
      
    }
    return avg;
}

#include <Entegre.h>

void setup() {
  Serial.begin(9600);
  delay(1500);
}

Entegre entegreler[] = {
  Entegre(8, 9, 10, 11, 7, 6),
  Entegre(8, 9, 10, 11, 7, 5)
};
EntegreYonetici yonetici(entegreler, sizeof(entegreler) / sizeof(Entegre));
int offset = 0;

void loop() {
  int toplam = 0;
  int ortalama = 0;

  // entegre sayisi kadar dondur
  for (int entegreIndex = 0; entegreIndex < sizeof(entegreler) / sizeof(Entegre); entegreIndex++) {
    // Her entegrenin tum kanallari icin dongu
    for (int channel = 0; channel < 16; channel++) {
      // Entegre yoneticisini kullanarak deger oku, acik kapali sonucunu bekle
      int sonuc = yonetici.readMux(entegreIndex, channel);
      if (sonuc == 1) {
        toplam += 1;  //toplama ekle döngü bitene kadar
      }
    }

    // hangi entegrede kac acik var yaz
    entegreler[entegreIndex].openDoor = toplam;
/*
    Serial.print("Entegre : ");
    Serial.print(entegreIndex);
    Serial.print(", Toplam Açık Sayısı : ");
    Serial.println(toplam);
   */ 
    toplam = 0;

    delay(250);
  }




  ortalama = yonetici.average(offset);
  Serial.println("******");
  Serial.print("SAG :");
  Serial.println(yonetici.rightCount());
  Serial.print("SOL :");
  Serial.println(yonetici.leftCount());
  Serial.print("Ortalama : ");
  
  Serial.println(ortalama);
  
}

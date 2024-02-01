# Entegre Kütüphanesi

Bu kütüphane, Arduino ile çeşitli entegreler arasında geçiş yaparak veri okumayı ve kontrol etmeyi kolaylaştırır. Entegrelerin kontrol pinleri ve sinyal pinleri üzerinden yönetimini sağlar, böylece karmaşık projelerde bile yapılandırılmış ve ölçeklenebilir bir çözüm sunar.

## Özellikler

- Birden fazla entegre ile çalışabilme
- Her entegre için 16 kanal desteği
- Entegrelerin kolayca aktif edilmesi ve devre dışı bırakılması
- Okuma ve kontrol işlemleri için temiz ve anlaşılır

## Kurulum

Bu kütüphaneyi Arduino IDE'ye dahil etmek için aşağıdaki adımları izleyin:

1. Bu repoyu `git clone https://github.com/Atakan-Demir/FabricAlignmentSensor` komutu ile klonlayın.
2. Klonladığınız klasörü Arduino'nun libraries klasörü içine kopyalayın.
3. Arduino IDE'yi yeniden başlatın.
4. İde içerisinde `#include <Entegre.h>` satırını ekleyerek kütüphaneyi projenize dahil edin.

## Kullanım

Kütüphaneyi kullanmaya başlamak için öncelikle `Entegre` ve `EntegreYonetici` sınıflarından nesneler oluşturmanız gerekmektedir. Aşağıda basit bir kullanım örneği verilmiştir:

```cpp
#include <Entegre.h>

// Entegre nesnelerini oluştur
Entegre entegre1(8, 9, 10, 11, 7, 4);
Entegre entegre2(8, 9, 10, 11, 7, 5);
Entegre entegreler[] = {entegre1, entegre2};

// Entegre yöneticisi nesnesini oluştur
EntegreYonetici yonetici(entegreler, 2);

void setup() {
  // Setup kodları...
}

void loop() {
  // Örnek olarak, birinci entegrenin 3. kanalından veri oku
  int deger = yonetici.readMux(0, 3);
  // Değeri kullan...
}

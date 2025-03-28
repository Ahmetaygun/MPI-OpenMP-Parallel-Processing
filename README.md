# Youtube linki : https://youtu.be/LIoZBjluekI

MPI ve OpenMP'nin Performans Karşılaştırması

1. Giriş

MPI (Message Passing Interface) ve OpenMP (Open Multi-Processing), paralel programlama için yaygın olarak kullanılan iki farklı teknolojidir. MPI, dağıtık bellekli sistemlerde işlemciler arası iletişimi sağlarken, OpenMP paylaşımlı bellek sistemlerinde çok çekirdekli işlem yapmayı kolaylaştırır. Bu raporda, MPI ve OpenMP'nin performans farkları analiz edilerek avantajları ve dezavantajları karşılaştırılmıştır.

2. Performans Karşılaştırması

Performans analizi için farklı ölçeklerde yapılan testlerde, aşağıdaki metrikler değerlendirilmiştir:

İşlem Süresi: Hesaplamaların toplam süresi

Hızlanma (Speedup): Paralel ve seri çalıştırmalar arasındaki hız farkı

Ölçeklenebilirlik: Çekirdek ve düğüm sayısının artmasıyla verim değişimi

Veri İletişim Gecikmesi: MPI'de düğümler arası veri transfer süresi

Senkronizasyon Maliyeti: OpenMP'de thread senkronizasyonunun etkisi

2.1 MPI Performansı

Avantajlar:

Büyük veri kümelerini işlemci düğümlerine dağıtarak verimli işlem yapar.

Dağıtık bellek sistemlerinde ölçeklenebilirliği yüksektir.

Her işlemci kendi belleğini kullandığı için bellek paylaşımından doğan darboğazlar yaşanmaz.

Dezavantajlar:

Düğümler arası iletişim maliyetlidir ve iletişim gecikmesi olabilir.

Kodlama süreci daha karmaşıktır ve veri bölme işlemleri dikkat gerektirir.

2.2 OpenMP Performansı

Avantajlar:

Aynı bellek alanını kullanan thread'ler sayesinde hızlı veri paylaşımı yapar.

Kodun MPI'ye göre daha basit bir şekilde paralelleştirilmesi mümkündür.

Küçük ve orta ölçekli problemlerde etkili performans sunar.

Dezavantajlar:

Ölçeklenebilirliği, sistemin çekirdek sayısı ile sınırlıdır.

Bellek erişiminde yoğun trafik oluşturabilir ve paylaşımlı bellek darboğazına neden olabilir.

Senkronizasyon ek yükü olabilir.

3. Sonuç

Yapılan testler sonucunda:

Küçük ölçekli işlemlerde OpenMP, düşük senkronizasyon maliyeti ve hızlı veri paylaşımı ile daha avantajlıdır.

Büyük ölçekli veri ve dağıtık sistemler için MPI, daha iyi ölçeklenebilirlik sunduğundan tercih edilmelidir.

 

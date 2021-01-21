# double to uint64_t

Pada repo ini, disimpan modul program C untuk mengubah data double menjadi uint64_t dan juga sebaliknya. Konversi antara dua tipe data ini harus dilakukan dengan pointer di C, tidak bisa dilakukan secara langsung menggunakan `static_cast<>` atau `(double)(uint64_t-var)` seperti di C++. 

Nilai uint64_t yang diperoleh akan aneh. Tapi tenang saja, jika diubah lagi menjadi double nilainya akan tetap sama dengan nilai aslinya. Silahkan dicoba. Anyway, referensi diperoleh dari [sini](https://stackoverflow.com/questions/42878158/cast-double-to-int64-t-and-back-without-info-lost)

(C) Muhammad Arifin

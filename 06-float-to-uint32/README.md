# Float to Uint32

Penjelasan:
- Pada repo ini, disimpan modul program C untuk mengubah data float menjadi uint32_t dan juga sebaliknya. Modul ini merupakan perkembangan dari modul `double-to-uint64` yang sebelumnya dibuat. 
- Alasan dibuat float-to-uint32 adalah karena uint64 membutuhkan bytes 2x lipat lebih banyak daripada uint32. 
- Selain itu ketika dilakukan percobaan, konversi dari tof uint64 ke frame uwb uint8 dan dari frame uint8 ke data uint64 memberikan hasil yang tidak konsisten jika dibandingkan uint32. Oleh karena itu uint32 digunakan. 
- Tambahan. Range float juga cukup, seharusnya untuk data tof. Tinggal di tes nanti di frame uwb aslinya. 

(C) Muhammad Arifin

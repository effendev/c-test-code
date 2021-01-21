# TOF to UWB Frame

Penjelasan:
- Pada repository ini disimpan modul program untuk menyisipkan data tof yang bertipe data float ke frame uint8. 
- Setelah disisipkan, data akan diambil lagi dari frame seolah-olah sudah diterima oleh anchor lain atau tag. 
- Untuk menyisipkan data tof digunakan fungsi `set_data32(...)` dan `floatToUint32(...)`. 
- Untuk mengekstrak data tof digunakan fungsi `get_data32(...)` dan `uint32ToFloat(...)`. 

(C) Muhammad Arifin

# Check Anchor In List

#### Tentang Repo:
Repository ini menyimpan kode tes dari fungsi `checkAnchorInList(..)`. Fungsi ini digunakan untuk mengecek apakah kita sudah pernah menerima pesan dari anchor yang pesannya baru saja kita terima ini, dalam satu siklus tdoa. Berikut adalah definisi fungsi tersebut. 

```c
// Function to find received anchor in struct storage
static bool checkAnchorInList(uint8_t* rx_buffer) {
	bool found = false;
	for(int i = 0; i < NUM_ANCHOR_MAX; i++) {
		uint16_t temp_id = receivedAnchorData[i].id;
		uint16_t rx_id = (uint16_t)(rx_buffer[1] << 8) | rx_buffer[2];
		if(temp_id == rx_id) {
			found = true;
			break;
		} else {
			continue;
		}
	}
	return found;
}
```

#### Penjelasan Program:
Berikut adalah poin-poin penting dalam file tes tersebut:
- Tes ini merupakan tes lanjutan dari tes untuk fungsi `initReceivedAnchorData(..)`.
- Pada program tes, dilakukan sedikit modifikasi pada fungsi `initReceivedAnchorData(..)` yang [dibahas disini](https://git.delameta.id/muhammad.arifin/tdoa-delameta/-/tree/arifin-dev/tdoa-tag/tests/initialize-received-anchor-data) sebelumnya. 
- Tes bertujuan untuk mengecek, apakah fungsi benar-benar memberikan respon `true` jika ID anchor sudah pernah disimpan dan `false` jika belum pernah. 
- Pada tes program, dua ID sudah pernah diterima pesannya oleh tag sedangkan satu ID belum pernah. 

(C) Muhammad Arifin

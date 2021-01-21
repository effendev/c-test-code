# Initialize Receive Anchor Data

#### Tentang Repo:
Repository ini menyimpan program tes untuk fungsi `initReceivedAnchorData()`. Program dibuat dari pengembangan program open-source milik [Bitcraze](https://github.com/bitcraze/lps-node-firmware/blob/master/src/uwb_tdoa_anchor3.c). 

#### Penjelasan Program:
Seperti yang dapat dilihat pada struktur program, fungsi ini menerima pointer dari variable `receivedAnchorData` dengan tipe data struct `receivedAnchorData_t`. Awalnya fungsi ini ingin dibuat menerima langsung `receivedAnchorData` dalam bentuk array. Tapi supaya lebih bersih, maka implementasinya dibuat sederhana dan array akan di loop pada bagian program yang memanggil fungsi ini. Lihat kode tes untuk lebih jelasnya. 

(C) Muhammad Arifin

#include <iostream>

using namespace std;

const int maxBarang = 100;
struct Barang {
    string nama;
    int harga;
    int stok;
};

Barang daftarBarang[maxBarang];
int jumlahBarang = 0;

void inputData() {
    if (jumlahBarang >= maxBarang) {
        cout << "Penyimpanan penuh! Tidak bisa menambahkan barang lagi.\n";
        return;
    }

    while (true) {
        cout << "Masukkan nama barang: ";
        cin >> daftarBarang[jumlahBarang].nama;
        
        cout << "Masukkan harga barang: ";
        cin >> daftarBarang[jumlahBarang].harga;

        cout << "Masukkan stok barang: ";
        cin >> daftarBarang[jumlahBarang].stok;

        jumlahBarang++;
        cout << "Data berhasil ditambahkan!\n";

        char lanjut;
        cout << "Tambah barang lagi? (y/n): ";
        cin >> lanjut;
        if (lanjut != 'y' && lanjut != 'Y') {
            break;
        }

        if (jumlahBarang >= maxBarang) {
            cout << "Penyimpanan penuh! Tidak bisa menambahkan barang lagi.\n";
            break;
        }
    }
}

void sortBarang() {
    for (int i = 0; i < jumlahBarang - 1; i++) {
        for (int j = 0; j < jumlahBarang - i - 1; j++) {
            if (daftarBarang[j].nama > daftarBarang[j + 1].nama) {
                swap(daftarBarang[j], daftarBarang[j + 1]);
            }
        }
    }
}

void tampilkanData() {
    if (jumlahBarang == 0) {
        cout << "Belum ada data barang!\n";
        return;
    }

    sortBarang(); 

    cout << "\n=== DAFTAR BARANG ===\n";
    for (int i = 0; i < jumlahBarang; i++) {
        cout << "Nama: " << daftarBarang[i].nama
             << ", Harga: " << daftarBarang[i].harga
             << ", Stok: " << daftarBarang[i].stok << endl;
    }
}

int binarySearch(string nama) {
    int kiri = 0, kanan = jumlahBarang - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (daftarBarang[tengah].nama == nama) {
            return tengah;
        } else if (daftarBarang[tengah].nama < nama) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    return -1;
}

void sequentialSearch(int harga) {
    bool ditemukan = false;
    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].harga == harga) {
            cout << "Nama: " << daftarBarang[i].nama
                 << ", Harga: " << daftarBarang[i].harga
                 << ", Stok: " << daftarBarang[i].stok << endl;
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        cout << "Tidak ada barang dengan harga tersebut!\n";
    }
}

void pencarianData() {
    if (jumlahBarang == 0) {
        cout << "Belum ada data barang untuk dicari!\n";
        return;
    }

    while (true) {
        cout << "\n=== PENCARIAN DATA ===\n";
        cout << "1. Cari berdasarkan Nama (Binary Search)\n";
        cout << "2. Cari berdasarkan Harga (Sequential Search)\n";
        cout << "3. Kembali ke menu utama\n";
        cout << "Pilih metode pencarian: ";

        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            string nama;
            cout << "Masukkan nama barang yang dicari: ";
            cin >> nama;

            sortBarang();

            int index = binarySearch(nama);
            if (index != -1) {
                cout << "Barang ditemukan: Nama: " << daftarBarang[index].nama
                     << ", Harga: " << daftarBarang[index].harga
                     << ", Stok: " << daftarBarang[index].stok << endl;
            } else {
                cout << "Barang tidak ditemukan!\n";
            }
        } else if (pilihan == 2) {
            int harga;
            cout << "Masukkan harga barang yang dicari: ";
            cin >> harga;
            sequentialSearch(harga);
        } else if (pilihan == 3) {
            break;
        } else {
            cout << "Pilihan tidak valid! Coba lagi.\n";
        }
    }
}

void menuUtama() {
    while (true) {
        cout << "\n=== TOKO KELONTONG B-2 ===\n";
        cout << "1. Input Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Pencarian Data\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";

        int menu;
        cin >> menu;

        if (menu == 1) {
            inputData();
        } else if (menu == 2) {
            tampilkanData();
        } else if (menu == 3) {
            pencarianData();
        } else if (menu == 4) {
            cout << "Terima kasih telah menggunakan sistem ini!\n";
            break;
        } else {
            cout << "Pilihan tidak valid! Silakan pilih menu yang tersedia.\n";
        }
    }
}
 
int main() {
    menuUtama();
    return 0;
}

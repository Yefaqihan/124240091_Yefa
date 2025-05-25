#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Mahasiswa {
    char nim[10];
    char nama[50];
};

struct Pohon {
    Mahasiswa data;
    Pohon *kiri, *kanan;
};

FILE *mhs;

Pohon* buatNode(const Mahasiswa &var) {
    Pohon *simpul = new Pohon;
    simpul->data = var;
    simpul->kiri = simpul->kanan = nullptr;
    return simpul;
}

Pohon* sisipData(Pohon *akar, const Mahasiswa &var) {
    if (!akar)
        return buatNode(var);
    if (strcmp(var.nim, akar->data.nim) < 0)
        akar->kiri = sisipData(akar->kiri, var);
    else if (strcmp(var.nim, akar->data.nim) > 0)
        akar->kanan = sisipData(akar->kanan, var);
    return akar;
}

bool cariNim(Pohon *akar, const char *nim, Mahasiswa &hasil) {
    if (!akar) return false;
    int cmp = strcmp(nim, akar->data.nim);
    if (cmp == 0) {
        hasil = akar->data;
        return true;
    } else if (cmp < 0) {
        return cariNim(akar->kiri, nim, hasil);
    } else {
        return cariNim(akar->kanan, nim, hasil);
    }
}

void inorder(Pohon *akar) {
    if (!akar) return;
    inorder(akar->kiri);
    cout << "NIM Mahasiswa  : " << akar->data.nim << endl;
    cout << "Nama Mahasiswa : " << akar->data.nama << endl;
    cout << "----------------------------------------" << endl;
    inorder(akar->kanan);
}

Pohon* simpulTerkiri(Pohon *akar) {
    while (akar && akar->kiri)
        akar = akar->kiri;
    return akar;
}

Pohon* hapusMhs(Pohon *akar, const char *nim, bool &dihapus) {
    if (!akar) return nullptr;
    int cmp = strcmp(nim, akar->data.nim);
    if (cmp < 0) {
        akar->kiri = hapusMhs(akar->kiri, nim, dihapus);
    } else if (cmp > 0) {
        akar->kanan = hapusMhs(akar->kanan, nim, dihapus);
    } else {
        dihapus = true;
        if (!akar->kiri) {
            Pohon *bantu = akar->kanan;
            delete akar;
            return bantu;
        } else if (!akar->kanan) {
            Pohon *bantu = akar->kiri;
            delete akar;
            return bantu;
        }
        Pohon *pengganti = simpulTerkiri(akar->kanan);
        akar->data = pengganti->data;
        akar->kanan = hapusMhs(akar->kanan, pengganti->data.nim, dihapus);
    }
    return akar;
}

Mahasiswa inputDataMhs() {
    Mahasiswa var;
    cout << "NIM Mahasiswa  : ";
    cin.getline(var.nim, 10);
    cout << "Nama Mahasiswa : ";
    cin.getline(var.nama, 50);
    return var;
}

void simpanDataKeFile(Pohon *akar, FILE *file) {
    if (!akar) return;
    simpanDataKeFile(akar->kiri, file);
    fwrite(&akar->data, sizeof(Mahasiswa), 1, file);
    simpanDataKeFile(akar->kanan, file);
}

void simpanDataMhsKeFile(Pohon *akar) {
    mhs = fopen("mhs.dat", "wb");
    if (!mhs) {
        cout << "[!] Gagal membuka file untuk menyimpan.\n";
        return;
    }
    simpanDataKeFile(akar, mhs);
    fclose(mhs);
}

Pohon* muatDataMhsDariFile() {
    mhs = fopen("mhs.dat", "rb");
    if (!mhs) return nullptr;

    Mahasiswa temp;
    Pohon *akar = nullptr;
    while (fread(&temp, sizeof(Mahasiswa), 1, mhs)) {
        akar = sisipData(akar, temp);
    }
    fclose(mhs);
    return akar;
}

void menuUtama() {
    Pohon *akar = muatDataMhsDariFile();

    while (true) {
        cout << "\n=== Pohon Biner Pencarian ===\n";
        cout << "1. Tambah Mahasiswa\n";
        cout << "2. Tampilkan Semua Mahasiswa (Inorder)\n";
        cout << "3. Cari Mahasiswa (Berdasarkan NIM)\n";
        cout << "4. Hapus Data Mahasiswa\n";
        cout << "5. Keluar\n";
        cout << "Pilih Menu: ";
        int pilihan;
        cin >> pilihan;
        cin.ignore(); 

        switch (pilihan) {
        case 1: {
            Mahasiswa var = inputDataMhs();
            Mahasiswa cek;
            if (cariNim(akar, var.nim, cek)) {
                cout << "[!] NIM sudah ada, tidak bisa disisipkan.\n";
            } else {
                akar = sisipData(akar, var);
                simpanDataMhsKeFile(akar);
                cout << "[+] Data berhasil ditambahkan.\n";
            }
            break;
        }
        case 2:
            if (!akar) {
                cout << "Belum ada data mahasiswa.\n";
            } else {
                cout << "\n-- Daftar Mahasiswa Secara Inorder --\n";
                inorder(akar);
            }
            break;
        case 3: {
            char cari[10];
            cout << "Masukkan NIM Mahasiswa yang dicari: ";
            cin.getline(cari, 10);
            Mahasiswa hasil;
            if (cariNim(akar, cari, hasil)) {
                cout << "\n>>> Mahasiswa Ditemukan:\n";
                cout << "NIM  : " << hasil.nim << endl;
                cout << "Nama : " << hasil.nama << endl;
            } else {
                cout << "Mahasiswa tidak ditemukan.\n";
            }
            break;
        }
        case 4: {
            char hapusNim[10];
            cout << "Masukkan NIM Mahasiswa yang akan dihapus: ";
            cin.getline(hapusNim, 10);
            bool dihapus = false;
            akar = hapusMhs(akar, hapusNim, dihapus);
            if (dihapus) {
                simpanDataMhsKeFile(akar);
                cout << "[-] Mahasiswa berhasil dihapus.\n";
            } else {
                cout << "Mahasiswa tidak ditemukan.\n";
            }
            break;
        }
        case 5:
            cout << "Terima kasih telah menggunakan Binary Search Tree!\n";
            return;
        default:
            cout << "Pilihan tidak tersedia!\n";
        }
    }
}

int main() {
    menuUtama();
    return 0;
}

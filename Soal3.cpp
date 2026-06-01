#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

struct Barang {
    string kodebarang;
    string namabarang;
    int harga;
    int stok;
};

void tambahbarang(vector<Barang>& daftarbarang) {
    Barang b;

    cout << "=== Tambah Barang ===" << endl;
    cout << "Kode Barang: ";
    cin >> b.kodebarang;

    cout << "Nama Barang: ";
    cin.ignore();
    getline(cin, b.namabarang);

    do {
        cout << "Harga: ";
        cin >> b.harga;
        if (b.harga < 0) {
            cout << "Error: Harga tidak boleh negatif!" << endl;
        }
    } while (b.harga < 0);

    do {
        cout << "Stok: ";
        cin >> b.stok;
        if (b.stok < 0) {
            cout << "Error: Stok tidak boleh negatif!" << endl;
        }
    } while (b.stok < 0);

    daftarbarang.push_back(b);
    cout << "Barang berhasil ditambahkan!" << endl;
}

void tampilkanbarang(const vector<Barang>& daftarbarang) {
    cout << "=== Daftar Barang ===" << endl;

    if (daftarbarang.empty()) {
        cout << "Belum ada data barang." << endl;
        return;
    }

    for (int i = 0; i < daftarbarang.size(); i++) {
        cout << "Barang ke-" << i + 1 << endl;
        cout << "Kode  : " << daftarbarang[i].kodebarang << endl;
        cout << "Nama  : " << daftarbarang[i].namabarang << endl;
        cout << "Harga : " << daftarbarang[i].harga << endl;
        cout << "Stok  : " << daftarbarang[i].stok << endl;
    }
}

void caribarangtermahal(const vector<Barang>& daftarbarang) {
    if (daftarbarang.empty()) {
        cout << "Data kosong!" << endl;
        return;
    }

    Barang maxbarang = daftarbarang[0];

    for (const auto& b : daftarbarang) {
        if (b.harga > maxbarang.harga) {
            maxbarang = b;
        }
    }
    cout << endl;

    cout << "=== Barang Termahal ===" << endl;
    cout << "Kode  : " << maxbarang.kodebarang << endl;
    cout << "Nama  : " << maxbarang.namabarang << endl;
    cout << "Harga : " << maxbarang.harga << endl;
    cout << "Stok  : " << maxbarang.stok << endl;
}

void hitungtotalnilai(const vector<Barang>& daftarbarang) {
    int total = 0;

    for (const auto& b : daftarbarang) {
        total += b.harga * b.stok;
    }

    cout << "Total Nilai Inventaris: " << total << endl;
}

void cekrestock(const vector<Barang>& daftarbarang) {
    cout << "=== Barang yang Perlu di Restock (Stok < 5) ===" << endl;

    bool ada = false;

    for (const auto& b : daftarbarang) {
        if (b.stok < 5) {
            cout << "- " << b.namabarang << " (Stok: " << b.stok << ")" << endl;
            ada = true;
        }
    }

    if (!ada) {
        cout << "Tidak ada barang yang perlu restock." << endl;
    }
}

void updatestok(vector<Barang>& daftarbarang) {
    string kode;
    int perubahan;
    cout << "Masukkan kode barang: ";
    cin >> kode;

    for (auto& b : daftarbarang) {
        if (b.kodebarang == kode) {

            do {
                cout << "Masukkan perubahan stok : ";
                cin >> perubahan;

                if (b.stok + perubahan < 0) {
                    cout << "Error: Stok tidak boleh kurang dari 0!" << endl;
                }

            } while (b.stok + perubahan < 0);

            int *ptrstok = &b.stok;
            *ptrstok += perubahan;

            cout << "Stok sekarang: " << b.stok << endl;
            return;
        }
    }

    cout << "Barang tidak ditemukan!" << endl;
}

int main() {
    vector<Barang> daftarbarang;
    int menu;

    do {
        system("cls");

        cout << "===== MENU INVENTARIS TOKO =====" << endl;
        cout << "1. Tambah Barang" << endl;
        cout << "2. Tampilkan Semua Barang" << endl;
        cout << "3. Cari Barang Termahal" << endl;
        cout << "4. Hitung Total Nilai Inventaris" << endl;
        cout << "5. Cek Restock" << endl;
        cout << "6. Update Stok" << endl;
        cout << "7. Keluar" << endl;
        cout << "===============================" << endl;
        cout << "Pilih menu : ";
        cin >> menu;

        system("cls");

        switch (menu) {
            case 1: tambahbarang(daftarbarang); break;
            case 2: tampilkanbarang(daftarbarang); break;
            case 3: caribarangtermahal(daftarbarang); break;
            case 4: hitungtotalnilai(daftarbarang); break;
            case 5: cekrestock(daftarbarang); break;
            case 6: updatestok(daftarbarang); break;
            case 7: cout << "Terima kasih, See you :)"; break;
            default: cout << "Menu tidak valid!";
        }

        if (menu != 7) {
            system("pause");
        }

    } while (menu != 7);

    return 0;
}

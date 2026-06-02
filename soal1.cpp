#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>
#include <ctime>

struct Petugas
{
    std::string nama;
    std::string id;
};

struct Mobil
{
    std::string plat;
    std::string merk;
    std::string warna;
    time_t wkt_masuk;
};

void addCar(Mobil daftarMobil[], int &jumlahMobilSaatIni, int MAX_MOBIL)
{
    int n;
    system("cls");
    if (jumlahMobilSaatIni >= MAX_MOBIL)
    {
        std::cout << "MOHON MAAF, KAPASITAS PARKIR PENUH! (Maksimal 20 Mobil)\n";
        system("pause");
        return;
    }
    int sisaSlot = MAX_MOBIL - jumlahMobilSaatIni;
    std::cout << "Sisa slot parkir: " << sisaSlot << " mobil.\n";
    std::cout << "Masukkan jumlah mobil yang akan diparkirkan : " << std::endl;
    std::cin >> n;

    if (std::cin.fail() || n <= 0 || n > sisaSlot)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input tidak valid atau melebihi sisa slot. Kembali ke menu.\n";
        system("pause");
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < n; i++)
    {
        std::cout << "Mobil ke " << i + 1 << std::endl;
        std::cout << "Masukkan plat mobil : " << std::endl;
        getline(std::cin, daftarMobil[jumlahMobilSaatIni].plat);
        std::cout << "Masukkan merk mobil : " << std::endl;
        getline(std::cin, daftarMobil[jumlahMobilSaatIni].merk);
        std::cout << "Masukkan warna mobil : " << std::endl;
        std::cin >> daftarMobil[jumlahMobilSaatIni].warna;
        std::cout << " " << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        daftarMobil[jumlahMobilSaatIni].wkt_masuk = time(0);
        jumlahMobilSaatIni++;
    }
}

void showCar(const Mobil daftarMobil[], int jumlahMobilSaatIni)
{
    time_t sekarang = time(0);
    system("cls");
    std::cout << "DAFTAR MOBIL YANG SUDAH TERPARKIR : " << std::endl;
    std::cout << "=============================================================" << std::endl;
    if (jumlahMobilSaatIni == 0)
    {
        std::cout << "\n[INFO] Belum ada kendaraan yang terdaftar di sistem saat ini.\n\n";
        system("pause");
        return;
    }
    else
    {
        for (int i = 0; i < jumlahMobilSaatIni; i++)
        {
            std::cout << "Mobil ke-" << i + 1 << std::endl;
            std::cout << "Plat mobil : " << daftarMobil[i].plat << std::endl;
            std::cout << "Merk mobil : " << daftarMobil[i].merk << std::endl;
            std::cout << "Warna mobil : " << daftarMobil[i].warna << std::endl;

            int selisih = sekarang - daftarMobil[i].wkt_masuk;
            int jam = selisih / 3600;
            int sisa_detik = selisih % 3600;
            int menit = sisa_detik / 60;
            int detik = sisa_detik % 60;
            std::cout << "Waktu parkir : " << jam << " jam " << menit << " menit " << detik << " detik" << std::endl;
            std::cout << "=============================================================" << std::endl;
        }
        system("pause");
    }
}

void payCar(Mobil daftarMobil[], int &jumlahMobilSaatIni)
{
    system("cls");
    std::cout << "                      PEMBAYARAN                       " << std::endl;
    std::cout << "=============================================================" << std::endl;
    if (jumlahMobilSaatIni == 0)
    {
        std::cout << "\n[INFO] Parkiran saat ini kosong.\n\n";
        system("pause");
        return;
    }

    std::cout << "[DAFTAR KENDARAAN TERPARKIR SAAT INI]" << std::endl;
    for (int i = 0; i < jumlahMobilSaatIni; i++)
    {
        std::cout << i + 1 << ". " << daftarMobil[i].plat << " (" << daftarMobil[i].merk << ")" << std::endl;
    }
    std::cout << "-------------------------------------------------------------" << std::endl;

    std::string platInput;
    bool isFound = false;
    while (!isFound)
    {
        std::cout << "Masukkan plat mobil yang ingin dibayar (ketik 0 untuk kembali): ";
        getline(std::cin, platInput);

        if (platInput == "0") return;

        for (int i = 0; i < jumlahMobilSaatIni; i++)
        {
            if (daftarMobil[i].plat == platInput)
            {
                isFound = true;

                time_t waktuKeluar = time(0);
                int durasi_parkir = waktuKeluar - daftarMobil[i].wkt_masuk;

                int biaya = 2000 * ((durasi_parkir + 899) / 900);

                std::cout << "\nB I A Y A  P A R K I R : Rp" << biaya << std::endl;
                std::cout << "=============================================================" << std::endl;
                std::cout << "Tekan ENTER jika pembayaran sudah diterima...";
                std::cin.get();

                for (int j = i; j < jumlahMobilSaatIni - 1; j++)
                {
                    daftarMobil[j] = daftarMobil[j + 1];
                }
                jumlahMobilSaatIni--;
                std::cout << "\n[SUKSES] Pembayaran selesai. Kendaraan dihapus dari daftar.\n";
                system("pause");
                break;
            }
        }

        if (!isFound)
        {
            std::cout << "PLAT TIDAK DITEMUKAN !\n\n";
        }
    }
}

void showMenu(std::string nama, std::string id, Mobil daftarMobil[], int jumlahMobilSaatIni, int MAX_MOBIL)
{
    int menu{};
    bool isRunning = true;
    while (isRunning)
    {
        system("cls");
        std::cout << "Nama Petugas : " << nama << std::endl;
        std::cout << "ID Petugas : " << id;
        std::cout << " " << std::endl;
        std::cout << "                 TERIMAKASIH ATAS KERJASAMANYA               " << std::endl;
        std::cout << "-----------------S E L A M A T  B E R T U G A S--------------" << std::endl;
        std::cout << "=============================================================" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "[MENU]" << std::endl;
        std::cout << "[1] Tambahkan Daftar Kendaraan" << std::endl;
        std::cout << "[2] Tampilkan Daftar Kendaraan" << std::endl;
        std::cout << "[3] Pembayaran" << std::endl;
        std::cout << "[4] Keluar Program" << std::endl;
        std::cout << "Pilih Menu (1-4) : " << std::endl;
        std::cin >> menu;

        if (std::cin.fail() || menu < 1 || menu > 4)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls");
            std::cout << "ERROR : INPUT INVALID!" << std::endl;
            system("pause");
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            switch (menu)
            {
            case 1: addCar(daftarMobil, jumlahMobilSaatIni, MAX_MOBIL); break;
            case 2: showCar(daftarMobil, jumlahMobilSaatIni); break;
            case 3: payCar(daftarMobil, jumlahMobilSaatIni); break;
            case 4: isRunning = false; break;
            default: break;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    const int MAX_MOBIL = 20;
    Mobil daftarMobil[MAX_MOBIL];
    int jumlahMobilSaatIni = 0;
    system("cls");
    std::cout << "=============================================================" << std::endl;
    std::cout << "------------------S E L A M A T  D A T A N G-----------------" << std::endl;
    std::cout << "                DI PORTAL PARKIR KHUSUS MOBIL                " << std::endl;
    std::cout << "                        MALL PRIENAL                         " << std::endl;
    std::cout << "=============================================================" << std::endl;
    std::cout << "Kami senang Anda telah hadir." << std::endl;
    std::cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini." << std::endl;
    std::cout << " " << std::endl;
    Petugas dataPetugas;
    std::cout << "Masukkan Nama : ";
    getline(std::cin, dataPetugas.nama);
    std::cout << "Masukkan ID : ";
    std::cin >> dataPetugas.id;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    showMenu(dataPetugas.nama, dataPetugas.id, daftarMobil, jumlahMobilSaatIni, MAX_MOBIL);
    return 0;
}

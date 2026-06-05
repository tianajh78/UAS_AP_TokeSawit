#include "project_2.h"
#include <chrono>
#include <thread>

using this_thread::sleep_for;
using chrono::seconds;

int main () {
    system ("Cls");
    srand (time(0));

    char ulang;
    do {
        system ("Cls");

        int pilihan, maxsalah, mult;

        cout << "--Tebak Kata Lemonade--" << endl;
        cout << endl;
        cout << "Pilih kesulitan :" << endl;
        cout << "1. Easy   (8 kesalahan)" << endl;
        cout << "2. Medium (6 kesalahan)" << endl;
        cout << "3. Hard   (4 kesalahan)" << endl;
        cout << "Pilihan : ";
        pilihan = getch ();

        if (pilihan == '1') {
            maxsalah = 8; mult = 1; }
        else if (pilihan == '2') {
            maxsalah = 6; mult = 2; }
        else if (pilihan == '3') {
            maxsalah = 4; mult = 3; }
        else {
            cout << endl << "1, 2, dan 3 aja loh. Heran" << endl;
            sleep_for (seconds(2));
            continue;
        }

        cout << endl;

        Kata game;
        awalgame (&game, bankkata[rand() % tokat], maxsalah);

        cout << "Tebaklah : " << strlen (game.kata) << " huruf. " << endl;
        cout << "pencet '?' kalau buntu tapi -1 nyawa ya" << endl;
        sleep_for (seconds(3));

        while (game.nyawa > 0 && !cekmenang (&game)) {
            system ("Cls");
            tampilstatus (&game, maxsalah);

            char huruf;
            cout << "Tebak huruf : ";
            huruf = getche ();
            cout << endl;

            if (huruf == '?') {
                hint (&game);
                sleep_for (seconds(1));
                continue;
            }

            huruf = tolower (huruf);

            if (!isalpha (huruf)) {
                cout << "Masukkan huruf" << endl;
                sleep_for (seconds(1));
                continue;
            }

            if (cekditebak (&game, huruf)) {
                cout << "Huruf '" << (char)toupper (huruf) << "' sudah ditebak!" << endl;
                sleep_for (seconds(1));
                continue;
            }

            if (tebakan (&game, huruf)) {
                cout << "Hebat ya benar" << endl;
                sleep_for (seconds(1));
            } else {
                cout << "When yah benar" << endl;
                cout << "Sisa nyawa loh ini liat : " << game.nyawa << endl;
                sleep_for (seconds(1));
            }
        }

        system ("Cls");
        tampilstatus (&game, maxsalah);

        int skor;
        if (cekmenang (&game)) {
            skor = hitungskor (&game, mult);
            cout << "Horeee, benar. " << endl;
            cout << "Kata rahasianya : " << game.kata << endl;
            cout << "Skor kamu : " << skor << " poin" << endl;
        } else {
            skor = 0;
            cout << "Yahahah Hayukk Kalah! " << endl;
            cout << "Kata rahasianya itu : " << game.kata << endl;
            cout << "Skor kamu : 0 poin" << endl;
        }

        cout << endl;
        char nama[50];
        cout << "Masukkan nama : ";
        cin.getline (nama, 50);
        simpanskor (nama, skor);

        tampillb ();

        cout << "Main lagi? (y/n) : ";
        ulang = getch ();
        cout << endl;

    } while (tolower (ulang) == 'y');

    system ("Cls");
    cout << "Ya Makasih ya." <<endl;
    cout << "Stream Lemonade - Aespa janlup" << endl;
}
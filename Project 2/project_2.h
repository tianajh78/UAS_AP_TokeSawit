#ifndef project_2_h
#define project_2_h

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <conio.h>
using namespace std;

const int tokat   = 15;
const int pankat  = 30;
const int maxlb   = 5;

const char bankkata[tokat][pankat] = {
    "bangku", "kursi", "lemari", "buku", "pensil",
    "meja", "papan", "kotak", "jaehyun", "album",
    "aespa", "pulpen", "telepon", "rautan", "buah"
};

struct Kata {
    char kata[pankat];
    char status[pankat];
    int  nyawa;
    char salah[26];
    int  jumsalah;
};

struct Skor {
    char nama[50];
    int  skor;
};

Skor lb[maxlb];
int jumlah = 0;


void awalgame (Kata *game, const char *kata, int nyawa) {
    strcpy (game->kata, kata);
    //strcpy (tujuan, sumeber)

    int panjang = strlen (kata);
    for (int i = 0; i < panjang; i++)
        game->status[i] = '_';
    game->status[panjang] = '\0';

    game->nyawa    = nyawa;
    game->jumsalah = 0;
    memset (game->salah, 0, sizeof (game->salah));
    // memset (alamat, nilai, jumlah byte);
}


int tebakan (Kata *game, char huruf) {
    int ketemu  = 0;
    int panjang = strlen (game->kata);

    for (int i = 0; i < panjang; i++) {
        if ((char)tolower (game->kata[i]) == huruf) {
            game->status[i] = game->kata[i];
            ketemu = 1;
        }
    }

    if (!ketemu) {
        game->salah[game->jumsalah] = huruf;
        game->jumsalah++;
        game->nyawa--;
    }

    return ketemu;
}


int cekditebak (Kata *game, char huruf) {
    for (int i = 0; i < (int)strlen (game->status); i++)
        if ((char)tolower (game->status[i]) == huruf) return 1;

    for (int i = 0; i < game->jumsalah; i++)
        if (game->salah[i] == huruf) return 1;

    return 0;
}


int cekmenang (Kata *game) {
    return strchr (game->status, '_') == NULL;
            //strcher (string, yg dicari)
}


void tampilstatus (Kata *game, int makssalah) {
    cout << "Kata  : ";
    for (int i = 0; i < (int)strlen (game->status); i++)
        cout << game->status[i] << " ";
    cout << endl;

    cout << "Nyawa : " << game->nyawa << "/" << makssalah << endl;

    cout << "Salah : ";
    if (game->jumsalah == 0)
        cout << "-";
    else
        for (int i = 0; i < game->jumsalah; i++)
            cout << (char)toupper (game->salah[i]) << " ";
    cout << endl << endl;
}


void hint (Kata *game) {
    if (game->nyawa <= 1) {
        cout << "Nyawa tidak cukup untuk hint!" << endl;
        return;
    }
    int panjang = strlen (game->kata);
    for (int i = 0; i < panjang; i++) {
        if (game->status[i] == '_') {
            char h = tolower (game->kata[i]);
            for (int j = 0; j < panjang; j++)
                if ((char)tolower (game->kata[j]) == h)
                    game->status[j] = game->kata[j];
            game->nyawa--;
            cout << "Hint: huruf '" << h << "' dibuka! -1 nyawa." << endl;
            return;
        }
    }
}


int hitungskor (Kata *game, int mult) {
    return game->nyawa * 10 * (int)strlen (game->kata) * mult;
}


void simpanskor (const char *nama, int skor) {
    if (jumlah < maxlb) {
        strcpy (lb[jumlah].nama, nama);
        lb[jumlah].skor = skor;
        jumlah++;
    } else {
        int idxmin = 0;
        for (int i = 1; i < maxlb; i++)
            if (lb[i].skor < lb[idxmin].skor) idxmin = i;
        if (skor > lb[idxmin].skor) {
            strcpy (lb[idxmin].nama, nama);
            lb[idxmin].skor = skor;
        }
    }
    for (int i = 0; i < jumlah - 1; i++)
        for (int j = 0; j < jumlah - 1 - i; j++)
            if (lb[j].skor < lb[j+1].skor) {
                Skor tmp   = lb[j];
                lb[j]      = lb[j+1];
                lb[j+1]    = tmp;
            }
}


void tampillb () {
    cout << "--- Leaderboard Top " << maxlb << " ---" << endl;
    if (jumlah == 0) {
        cout << "Belum ada skor." << endl;
        return;
    }
    for (int i = 0; i < jumlah; i++)
        cout << i+1 << ". " << lb[i].nama << " - " << lb[i].skor << " poin" << endl;
    cout << endl;
}

#endif
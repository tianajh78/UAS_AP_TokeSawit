#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct Negara {
    string nama;
    vector<string> versiSoal;
};

int main() {
    system("cls");
    srand(time(0));

    vector<Negara> daftarNegara = {
        {"Amerika", {"Am_r__a", "_me_i_a", "Am__ik_", "A_er_ka"}},
        {"Indonesia", {"I__o__si_", "_ndo_e_ia", "Ind____sia"}},
        {"Malaysia", {"M_l__si_", "_alays__"}},
        {"Singapura", {"S__ga__ra", "_ingap_ra", "S_ng__u_a"}},
        {"Thailand", {"T__il__d", "_hai_an_"}},
        {"Jepang", {"J_p__g", "_ep_ng"}},
        {"Kanada", {"K_n_d_", "_anad_"}},
        {"Brazil", {"B_a_i_", "_ra_il"}},
        {"Argentina", {"A_g_n_i__", "__gen_ina"}},
        {"Filipina", {"F_l_p_n_", "_ili__na"}}
    };

    int poin = 0;
    char lagi;

    cout << "\n===== TEBAK NEGARA =====" << endl;
    do {
        int indexNegara = rand() % daftarNegara.size();

        int indexSoal = rand() % daftarNegara[indexNegara].versiSoal.size();

        string jawabanBenar = daftarNegara[indexNegara].nama;
        string soal = daftarNegara[indexNegara].versiSoal[indexSoal];

        cout << endl;
        cout << soal << endl;

        string jawabanUser;
        cout << "-> ";
        cin >> jawabanUser;

        string jb = jawabanBenar;
        string ju = jawabanUser;

        transform(jb.begin(), jb.end(), jb.begin(), ::tolower);
        transform(ju.begin(), ju.end(), ju.begin(), ::tolower);

        if (ju == jb) {
            cout << "Benar!" << endl;
            poin++;
        } else {
            cout << "Salah!" << endl;
            cout << "Jawaban yang benar adalah: " << jawabanBenar << endl;
        }

        cout << "Skor: " << poin << endl;

        cout << "\nMain lagi? (y/n) : ";
        cin >> lagi;

    } while (lagi == 'y' || lagi == 'Y');

    cout << "\n===============" << endl;
    cout << "Game selesai!" << endl;
    cout << "Total skor : " << poin << endl;
    cout << "===============";

    return 0;
}
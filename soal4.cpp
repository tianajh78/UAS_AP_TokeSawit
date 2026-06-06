#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int N;
    int bombCount;

    bool bomb[10][10];
    bool opened[10][10];
    bool flagged[10][10];
    int number[10][10];

    bool gameOver;
    bool win;

    time_t startTime;
    time_t endTime;

    void initializeBoard() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                bomb[i][j] = false;
                opened[i][j] = false;
                flagged[i][j] = false;
                number[i][j] = 0;
            }
        }
    }

    void placeBombs() {
        int placed = 0;

        while (placed < bombCount) {
            int r = rand() % N;
            int c = rand() % N;

            if (!bomb[r][c]) {
                bomb[r][c] = true;
                placed++;
            }
        }
    }

    void calculateNumbers() {
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {

                if (bomb[r][c]) {
                    number[r][c] = -1;
                    continue;
                }

                int count = 0;

                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {

                        if (dr == 0 && dc == 0)
                            continue;

                        int nr = r + dr;
                        int nc = c + dc;

                        if (nr >= 0 && nr < N &&
                            nc >= 0 && nc < N &&
                            bomb[nr][nc]) {
                            count++;
                        }
                    }
                }

                number[r][c] = count;
            }
        }
    }

    void floodFill(int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N)
            return;

        if (opened[r][c] || flagged[r][c])
            return;

        if (bomb[r][c])
            return;

        opened[r][c] = true;

        if (number[r][c] != 0)
            return;

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (!(dr == 0 && dc == 0))
                    floodFill(r + dr, c + dc);
            }
        }
    }

    int remainingBombs() {
        int flags = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (flagged[i][j])
                    flags++;
            }
        }

        return bombCount - flags;
    }

    void revealBombs() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (bomb[i][j])
                    opened[i][j] = true;
            }
        }
    }

    bool checkWin() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                if (bomb[i][j] && !flagged[i][j])
                    return false;

                if (!bomb[i][j] && flagged[i][j])
                    return false;
            }
        }

        return true;
    }

public:
    Minesweeper() {
        gameOver = false;
        win = false;
    }

    void setup() {
        do {
            cout << "Ukuran papan (4-10): ";
            cin >> N;
        } while (N < 4 || N > 10);

        int maxBomb = N * N - 1;

        do {
            cout << "Jumlah bom (1-" << maxBomb << "): ";
            cin >> bombCount;
        } while (bombCount < 1 || bombCount > maxBomb);

        initializeBoard();
        placeBombs();
        calculateNumbers();

        gameOver = false;
        win = false;

        startTime = time(0);
    }

    void displayBoard() {
        cout << "\n";

        cout << "    ";
        for (int c = 0; c < N; c++) {
            cout << c + 1 << " ";
        }
        cout << "\n";

        for (int r = 0; r < N; r++) {

            if (r + 1 < 10)
                cout << " ";

            cout << r + 1 << "  ";

            for (int c = 0; c < N; c++) {

                if (flagged[r][c]) {
                    cout << "F ";
                }
                else if (!opened[r][c]) {
                    cout << "# ";
                }
                else if (bomb[r][c]) {
                    cout << "* ";
                }
                else {
                    cout << number[r][c] << " ";
                }
            }

            cout << "\n";
        }

        cout << "\nBom belum ditandai: "
             << remainingBombs() << "\n";

        cout << "Waktu: "
             << (int)(time(0) - startTime)
             << " detik\n";
    }

    void play() {

        while (!gameOver) {

            displayBoard();

            char action;
            int row, col;

            cout << "\nB = buka, T = tandai: ";
            cin >> action;

            cout << "Baris: ";
            cin >> row;

            cout << "Kolom: ";
            cin >> col;

            row--;
            col--;

            if (row < 0 || row >= N ||
                col < 0 || col >= N) {
                cout << "Koordinat tidak valid!\n";
                continue;
            }

            if (action == 'B' || action == 'b') {

                if (flagged[row][col]) {
                    cout << "Kotak ditandai!\n";
                    continue;
                }

                if (bomb[row][col]) {

                    revealBombs();

                    gameOver = true;
                    win = false;
                }
                else {

                    if (number[row][col] == 0)
                        floodFill(row, col);
                    else
                        opened[row][col] = true;
                }
            }
            else if (action == 'T' || action == 't') {

                if (!opened[row][col])
                    flagged[row][col] = !flagged[row][col];
            }

            if (checkWin()) {
                gameOver = true;
                win = true;
            }
        }

        endTime = time(0);

        displayBoard();

        cout << "\n====================\n";

        if (win)
            cout << "ANDA MENANG!\n";
        else
            cout << "GAME OVER!\n";

        cout << "Waktu bermain: "
             << (int)(endTime - startTime)
             << " detik\n";

        cout << "====================\n";
    }
};

int main() {
    srand(time(0));

    int choice;

    do {
        cout << "\n=== MINESWEEPER++ ===\n";
        cout << "1. Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;

        if (choice == 1) {
            Minesweeper game;
            game.setup();
            game.play();
        }

    } while (choice != 2);

    return 0;
}

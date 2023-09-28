#include <bits/stdc++.h>
using namespace std;

const int n = 9;

vector<vector<int>> sudoku;

void printSudoku() {
    cout << "-------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << "|  ";
        for (int j = 0; j < n; j++) {
            cout << sudoku[i][j] << "  ";
            if (j % 3 == 2) cout << "|  ";
        }
        cout << "\n";
        if (i % 3 == 2) cout << "-------------------------------------\n";
    }
    cout << "\n\n";
}

bool validar(int num, int r, int c) {
    for (int i=0; i<n; i++) {
        if (sudoku[r][i] == num) return 0;
        if (sudoku[i][c] == num) return 0;
    }

    int iq = r / 3 * 3;
    int jq = c / 3 * 3;
    
    for (int i = 0; i < 3 ; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[iq + i][jq + j] == num) 
                return 0;
        }
    }

    return 1;
}
void bt(int r, int c) { // k columna
    if (r == n) {
        printSudoku();
        return;
    }

    int nc = (c == n - 1) ? 0 : c + 1;
    int nr = (c == n - 1) ? r + 1 : r; // new row

    if (sudoku[r][c] != 0) {
        bt(nr,nc);
        return;
    }

    for (int num = 1; num <= n; num++) {
        if (validar(num, r, c)) {
            sudoku[r][c] = num;
            bt(nr,nc);
            sudoku[r][c] = 0;
        }
    }
}

int main() {
    sudoku = {
            {3, 0, 6, 5, 0, 8, 4, 0, 0},  
            {5, 2, 0, 0, 0, 0, 0, 0, 0},  
            {0, 8, 7, 0, 0, 0, 0, 3, 1},  
            {0, 0, 3, 0, 1, 0, 0, 8, 0},  
            {9, 0, 0, 8, 6, 3, 0, 0, 5},  
            {0, 5, 0, 0, 9, 0, 6, 0, 0},  
            {1, 3, 0, 0, 0, 0, 2, 5, 0},  
            {0, 0, 0, 0, 0, 0, 0, 7, 4},  
            {0, 0, 5, 2, 0, 6, 3, 0, 0}
           };
    bt(0,0);   
    return 0;
}
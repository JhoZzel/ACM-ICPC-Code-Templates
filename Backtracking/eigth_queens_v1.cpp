#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

char mat[10][10];

int eight_queen(int r[], int c) {
    if (c == 8) {
        memset(mat, '_', sizeof mat);
        for (int i=0; i<8; ++i) {
            mat[r[i]][i] = 'Q';
        }
        cout << endl;
        cout << endl;
        cout << "NEW SOLUTION: " << endl;
        for (int i=0; i<8; ++i) {
            cout << "|";
            for (int j = 0; j < 8; ++j) {
                cout << mat[i][j];
                cout << "|";
            }
            cout << endl;
        }
        cout << endl;
        return 1;
    }

    int cnt = 0;
    for (int i=0; i<8; i++) {
        bool can = true;
        for (int j=0; j<c; j++) {
            if (r[j]==i || abs(j-c)==abs(r[j]-i)) {
                can = false;
                break;
            }
        }
        if (can) {
            r[c]=i;
            cnt += eight_queen(r, c + 1);
        }
    }
    return cnt;
}


int main() {
    int r[10];
    cout << eight_queen(r,0) << "\n";
    return 0;
}

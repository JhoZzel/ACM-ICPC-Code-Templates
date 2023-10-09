#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

struct Matrix {
    int row;
    int col;

    vvl data;
    

    Matrix() : row(0), col(0) {}
    Matrix(int rows, int cols) : row(rows), col(cols), data(rows, vl(cols, 0)) {}

    vl& operator[](int i) {
        return data[i];
    }

    const vl& operator[](int i) const {
        return data[i];
    }

    friend istream& operator>>(istream& in, Matrix& A) {
        in >> A.row >> A.col;
        A.data.resize(A.row, vl(A.col));
        for (int i = 0; i < A.row; i++) {
            for (int j = 0; j < A.col; j++) {
                in >> A[i][j];
            }
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Matrix& A) {
        for (int i=0; i<A.row; i++) {
            for (int j=0; j<A.col; j++) {
                out << A[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }

    Matrix operator+(Matrix B) {
        Matrix C(row, col);   
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                C[i][j] = data[i][j] + B[i][j];
            }
        }
        return C;
    }

};

int main() {
    Matrix A,B;
    cin >> A >> B;
    Matrix C = A + B;
    
    return 0;
}


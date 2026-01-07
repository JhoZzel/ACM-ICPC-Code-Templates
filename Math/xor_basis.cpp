// Xor Basis
// 

const int LOG = 30;

int sz;
int B[LOG];

void insert(int mask) {
    for (int i = 0; i < LOG; i++) {
		if ((mask & 1 << i) == 0) continue;
        if (!B[i]) {
            B[i] = mask;
            sz++;
            return;
        }
        mask ^= B[i];
    }
}

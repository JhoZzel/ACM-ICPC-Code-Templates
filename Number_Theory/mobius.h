// Mobius and Euler's totient functions
//

const int MAX = 1e7 + 5;

int spf[MAX], mu[MAX], phi[MAX];
vector<int> pr;

void sieve() {
    mu[1] = phi[1] = 1;
    for (int i = 2; i < MAX; i++) {
        if (!spf[i]) {
            spf[i] = i;
            phi[i] = i - 1;
            mu[i] = -1;
            pr.push_back(i);
        }

        for (int p : pr) { 
            if (1ll * p * i >= MAX) break;
            int x = p * i;
            spf[x] = p;
            if (i % p == 0) {
                mu[x] = 0;
                phi[x] = phi[i] * p;
                break;
            }
            mu[x] = -mu[i];
            phi[x] = phi[i] * (p - 1);
        }
    }
}

vector<pair<int,int>> get_fact(int x) {
    vector<pair<int,int>> f;
    while(x != 1) {
        int p = spf[x];
        int e = 0;
        while(x % p == 0) {
            e++;
            x /= p;
        }
        f.emplace_back(p, e);
    }      
    return f;
}


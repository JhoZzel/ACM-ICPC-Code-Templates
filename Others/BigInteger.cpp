#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

class bint {
private:
    string num = "0";
    bool isNeg = 0;

    bool isValid(const string& s) {
        if (s.empty()) return 0;
        switch (s[0]) {
            case '+': case '-': break;
            default:
                if (!isdigit(s[0])) return 0;
        }
        for (int i = 1; i < sz(s); i++)
            if (!isdigit(s[i])) return 0;
        return 1;
    }

    bint convert(const string& s) {
        bint b;
        b.isNeg = (s[0] == '-');

        int i = (s[0] == '-' or s[0] == '+');
        while (i < sz(s) && s[i] == '0') i++;

        b.num = s.substr(i);
        if (b.num.empty()) b.num = "0";
        if (b.num == "0") b.isNeg = 0;
        return b;
    }

    int cmpAbs(const bint& b) const {
        if (sz(num) != sz(b.num)) return (sz(num) < sz(b.num) ? -1 : 1);
        if (num == b.num) return 0;
        return (num < b.num ? -1 : 1);
    }

public:
    bint() { num = "0"; isNeg = 0; }
    bint(string s) { assert(isValid(s)); *this = convert(s); }
    bint(int x) { *this = to_string(x); }

    friend istream& operator>>(istream& input, bint& b) {
        string s; input >> s;
        assert(b.isValid(s));
        b = b.convert(s);
        return input;
    }
    friend ostream& operator<<(ostream& output, const bint& b) {
        if (b.isNeg && b.num != "0") output << "-";
        output << b.num;
        return output;
    }

    void operator=(const bint& b) { num = b.num; isNeg = b.isNeg; }
    void operator=(const string& s) { assert(isValid(s)); *this = convert(s); }
    void operator=(const int& x) { *this = to_string(x); }

    bool operator>(const bint& b) {
        if (isNeg != b.isNeg) return b.isNeg;
        int c = cmpAbs(b);
        if (!isNeg) return c > 0;
        else return c < 0;
    }
    bool operator>=(const bint& b) { return (*this > b) || (*this == b); }
    bool operator<(const bint& b) { return !(*this >= b); }
    bool operator<=(const bint& b) { return !(*this > b); }
    bool operator==(const bint& b) { return num == b.num && isNeg == b.isNeg; }
    bool operator!=(const bint& b) { return !(*this == b); }

    bint operator+(const bint& b) {
        bool differentSigns = (b.isNeg ^ isNeg);
        bint result;

        if (differentSigns) {
            if (b.isNeg) result = convert(subtract(num, b.num));
            else         result = convert(subtract(b.num, num));
        } else {
            result = convert(add(num, b.num));
            result.isNeg = (isNeg && b.isNeg);
        }
        if (result.num == "0") result.isNeg = 0;
        return result;
    }

    bint operator-(const bint& b) {
        bool differentSigns = (b.isNeg ^ isNeg);
        bint result;

        if (differentSigns) {
            if (b.isNeg) result = convert(add(num, b.num));
            else {
                result = convert(add(b.num, num));
                result.isNeg = 1;
            }
        } else {
            if (!isNeg && !b.isNeg) result = convert(subtract(num, b.num));
            else                    result = convert(subtract(b.num, num));
        }
        if (result.num == "0") result.isNeg = 0;
        return result;
    }

    bint operator*(const bint& b) {
        bint result = convert(multiply(num, b.num));
        result.isNeg = (isNeg ^ b.isNeg);
        if (result.num == "0") result.isNeg = 0;
        return result;
    }

    bint operator/(const bint& b) {
        assert(b.num != "0");
        bint result = convert(divide(num, b.num));
        result.isNeg = (result.num != "0" && (isNeg ^ b.isNeg));
        return result;
    }

    bint operator%(const bint& b) {
        assert(b.num != "0");
        bint result = convert(modulo(num, b.num));
        result.isNeg = isNeg;
        if (result.num == "0") result.isNeg = 0;
        return result;
    }

private:
    string divideBy2(bint x) {
        int current = 0;
        string res = "";
        for (int i = 0; i < sz(x.num); i++) {
            current = current * 10 + (x.num[i]- '0');
            if (current < 2) {
                if (i > 0) res += '0';
            } else {
                res += char((current / 2) + '0');
                current %= 2;
            }
        }
        if (sz(res) == 0) return "0";
        return res;
    }

    string add(const string& a, const string& b) {
        string res = "";
        int i = sz(a) - 1, j = sz(b) - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int x = (i >= 0) ? a[i--] - '0' : 0;
            int y = (j >= 0) ? b[j--] - '0' : 0;
            int cur = x + y + carry;
            carry = cur / 10;
            cur %= 10;
            res += char(cur + '0');
        }
        reverse(res.begin(), res.end());
        return res;
    }

    string subtract(string a, string b) {
        if (sz(a) < sz(b) || (sz(a) == sz(b) && a < b)) {
            return "-" + subtract(b, a);
        }

        string res = "";
        int i = sz(a) - 1, j = sz(b) - 1;

        while (i >= 0 || j >= 0) {
            int x = a[i] - '0';
            int y = (j >= 0) ? b[j] - '0' : 0;

            if (y > x) {
                int k = i - 1;
                while (k >= 0 && a[k] == '0') { a[k] = '9'; k--; }
                if (k >= 0) a[k]--;
                x += 10;
            }

            int cur = x - y;
            res += char(cur + '0');
            i--; j--;
        }

        while (sz(res) > 1 && res.back() == '0') res.pop_back();
        reverse(res.begin(), res.end());
        return res;
    }

    using cd = complex<double>;
    const double PI = acos(-1.0);

    void fft(vector<cd>& a, bool invert) {
        int n = sz(a);
        if (n == 1) return;

        vector<cd> a0(n / 2), a1(n / 2);
        for (int i = 0; 2 * i < n; i++) {
            a0[i] = a[2 * i];
            a1[i] = a[2 * i + 1];
        }
        fft(a0, invert);
        fft(a1, invert);

        double ang = 2 * PI / n * (invert ? -1 : 1);
        cd w(1), wn(cos(ang), sin(ang));
        for (int i = 0; 2 * i < n; i++) {
            a[i] = a0[i] + w * a1[i];
            a[i + n / 2] = a0[i] - w * a1[i];
            if (invert) {
                a[i] /= 2;
                a[i + n / 2] /= 2;
            }
            w *= wn;
        }
    }

    string multiplyFFT(const string& a, const string& b) {
        int n1 = sz(a), n2 = sz(b);
        int n = 1;
        while (n < n1 + n2) n <<= 1;

        vector<cd> A(n), B(n);
        for (int i = 0, j = n1 - 1, k = n2 - 1; i < n; i++, j--, k--) {
            double av = (j >= 0) ? (a[j] - '0') : 0;
            double bv = (k >= 0) ? (b[k] - '0') : 0;
            A[i] = {av, 0.0};
            B[i] = {bv, 0.0};
        }

        fft(A, 0);
        fft(B, 0);

        vector<cd> C(n);
        for (int i = 0; i < n; i++) C[i] = A[i] * B[i];

        fft(C, 1);

        vector<int> Ans(n);
        for (int i = 0; i < n - 1; i++)
            Ans[n - i - 1] = (int)llround(C[i].real());

        for (int i = n - 1; i > 0; i--) {
            Ans[i - 1] += Ans[i] / 10;
            Ans[i] %= 10;
        }

        int i = 0;
        while (i < n && Ans[i] == 0) i++;
        if (i == n) return "0";

        string out;
        out.reserve(n + 1);
        while (i < n) out += char('0' + Ans[i++]);
        return out;
    }

    string multiply(const string& a, const string& b) { return multiplyFFT(a, b); }

    string divide(const string& a, const string& b) {
        if (b == "1") return a;

        bint L("0");
        bint R(a);
        bint one("1");
        bint aa(a), bb(b);

        while (R - L > one) {
            bint M = bint(divideBy2(L + R));
            if (M * bb <= aa) L = M;
            else R = M;
        }
        return L.num;
    }

    string modulo(const string& a, const string& b) {
        bint aa(a), bb(b);
        return (aa - ((aa / bb) * bb)).num;
    }
};

namespace MathFunctions {
    bint fibonacci(int n) {
        bint res;
        switch (n) {
            case 0: res = "0"; break;
            case 1: res = "1"; break;
            default: {
                bint t1("1"), t2("0");
                for (int cur = 1; cur < n; cur++) {
                    res = t1 + t2;
                    t2 = t1;
                    t1 = res;
                }
            }
        }
        return res;
    }

    bint factorial(int n) {
        bint res("1");
        for (int i = 2; i <= n; i++) res = res * bint(to_string(i));
        return res;
    }

    bint gcd(bint a, bint b) {
        if (b == bint("0")) return a;
        return gcd(b, a % b);
    }

    bint lcm(bint a, bint b) {
        return a * (b / gcd(a, b));
    }

    bint pow(bint x, bint n) {
        bint ans("1");
        while (n > bint("0")) {
            if (n % bint("2") == bint("1")) ans = ans * x;
            x = x * x;
            n = n / bint("2");
        }
        return ans;
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--) {
        bint a,b;
        cin >> a >> b;
        cout << a / b << " " << a % b << '\n';
    }

    return 0;
} 


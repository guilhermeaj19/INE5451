#include <bits/stdc++.h>

using namespace std;
#define ll long long

const long long MOD = 1000000007;
const long double PI = acosl(-1.0L);

struct cd {
    long double r, i;
    cd(long double r = 0, long double i = 0) : r(r), i(i) {}
    cd operator+(const cd& o) const { return cd(r + o.r, i + o.i); }
    cd operator-(const cd& o) const { return cd(r - o.r, i - o.i); }
    cd operator*(const cd& o) const { return cd(r * o.r - i * o.i, r * o.i + i * o.r); }
    cd conj() const { return cd(r, -i); }
};

ll power(ll base, ll exp) {
    ll result = 1;
    base = base % MOD;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

ll modInverse(ll n) {
    return power(n, MOD - 2);
}

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        long double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cosl(ang), sinl(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w = w * wlen;
            }
        }
    }
    if (invert) {
        for (int i = 0; i < n; i++) {
            a[i].r /= n;
            a[i].i /= n;
        }
    }
}

vector<ll> multiply_mod(vector<ll> const& a, vector<ll> const& b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;

    vector<cd> P(n), Q(n);
    int cut = 32768; 

    for (int i = 0; i < a.size(); i++) {
        P[i] = cd(a[i] % cut, a[i] / cut);
    }
    for (int i = 0; i < b.size(); i++) {
        Q[i] = cd(b[i] % cut, b[i] / cut);
    }

    fft(P, false); 
    fft(Q, false);

    vector<cd> C1(n), C2(n);
    for (int i = 0; i < n; i++) {
        int j = (n - i) % n;
        
        cd A1 = (P[i] + P[j].conj()) * cd(0.5, 0);
        cd A2 = (P[i] - P[j].conj()) * cd(0, -0.5);
        cd B1 = (Q[i] + Q[j].conj()) * cd(0.5, 0);
        cd B2 = (Q[i] - Q[j].conj()) * cd(0, -0.5);

        C1[i] = A1 * B1 + (A1 * B2 + A2 * B1) * cd(0, 1);
        C2[i] = A2 * B2;
    }

    fft(C1, true); 
    fft(C2, true);

    vector<ll> res(n);
    ll cut2 = (1LL * cut * cut) % MOD;
    
    for (int i = 0; i < n; i++) {
        ll v1 = (ll)roundl(C1[i].r) % MOD;
        ll v2 = (ll)roundl(C1[i].i) % MOD;
        ll v3 = (ll)roundl(C2[i].r) % MOD;
        
        v1 = (v1 + MOD) % MOD;
        v2 = (v2 + MOD) % MOD;
        v3 = (v3 + MOD) % MOD;

        res[i] = (v1 + (v2 * cut) % MOD + (v3 * cut2) % MOD) % MOD;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll k;
    if (!(cin >> k)) return 0;

    vector<ll> fact(k + 1, 1);
    vector<ll> invFact(k + 1, 1);

    for (int i = 1; i <= k; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    invFact[k] = modInverse(fact[k]);
    for (int i = k - 1; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    vector<ll> A(k + 1, 0), B(k + 1, 0);

    for (int i = 0; i <= k; i++) {
        A[i] = invFact[i];
        if (i % 2 != 0) {
            A[i] = (MOD - A[i]) % MOD;
        }
    }

    for (int i = 0; i <= k; i++) {
        B[i] = (power(i, k) * invFact[i]) % MOD;
    }

    vector<ll> C = multiply_mod(A, B);

    for (int i = 1; i <= k; i++) {
        ll ans = (fact[i] * C[i]) % MOD;
        cout << ans << (i == k ? "" : " ");
    }
    cout << "\n";

    return 0;
}
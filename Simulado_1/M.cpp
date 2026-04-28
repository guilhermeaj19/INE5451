#include <bits/stdc++.h>

using namespace std;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= 998244353;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % 998244353;
        base = (base * base) % 998244353;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, 998244353 - 2);
}

long long fact[6005], invFact[6005];

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= 6000; i++) fact[i] = (fact[i - 1] * i) % 998244353;
    invFact[6000] = modInverse(fact[6000]);
    for (int i = 5999; i >= 0; i--) invFact[i] = (invFact[i + 1] * (i + 1)) % 998244353;
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % 998244353 * invFact[n - r] % 998244353;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int p, s, r;
    cin >> p >> s >> r;
    precompute();

    long long total_states = nCr(s - r + p - 1, p - 1);
    long long favorable_sum = 0;

    for (int x = r; x <= s; x++) {
        for (int k = 1; k <= p; k++) {
            if (k * x > s) break;

            int rem_s = s - k * x;
            int rem_p = p - k;
            long long ways_to_distribute = 0;

            if (rem_p == 0) {
                if (rem_s == 0) ways_to_distribute = 1;
            } else {
                for (int i = 0; i <= rem_p; i++) {
                    int stars = rem_s - i * x;
                    if (stars < 0) break;
                    long long term = nCr(rem_p, i) * nCr(stars + rem_p - 1, rem_p - 1) % 998244353;
                    if (i % 2 == 1) ways_to_distribute = (ways_to_distribute - term + 998244353) % 998244353;
                    else ways_to_distribute = (ways_to_distribute + term) % 998244353;
                }
            }

            long long ways = nCr(p - 1, k - 1) * ways_to_distribute % 998244353;
            ways = ways * modInverse(k) % 998244353;
            favorable_sum = (favorable_sum + ways) % 998244353;
        }
    }

    cout << (favorable_sum * modInverse(total_states)) % 998244353 << endl;

    return 0;
}
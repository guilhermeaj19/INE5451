#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

ll modInverse(ll a, ll m) {
    ll m0 = m, t, q;
    ll x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

ll chinese_theorem(int mods[], int rems[], int n) {
    ll prod = 1;
    for (int i = 0; i < n; i++) {
        prod *= mods[i];
    }

    ll result = 0;
    for (int i = 0; i < n; i++) {
        ll pp = prod / mods[i];

        ll inv = modInverse(pp, mods[i]);
        ll term = (rems[i] * inv) % prod;
        term = (term * pp) % prod;
        
        result = (result + term) % prod;
    }

    return result;
}


int main() {
    int M = 108;
    cout << M << endl;
    cout.flush();

    int primes[9] = {4, 9, 5, 7, 11, 13, 17, 19, 23};

    int start[M];
    int f_start[M];

    for (int i = 0; i < M; i++) {
        start[i] = i + 1; 
    }

    int idx = 0;
    for (int p : primes) {
        for (int i = 0; i < p; i++) {

            int atual = idx + i;
            int proximo = idx + (i + 1) % p;
            
            f_start[atual] = start[proximo];
        }
        idx += p;
    }

    string output = "";
    for (int i = 0; i < M; i++) {
        output += to_string(f_start[i]) + " ";
    }
    cout << output << endl;
    cout.flush();


    int response[M];
    for (int i = 0; i < M; i++) {
        cin >> response[i];
    }

    int f_response[9];
    idx = 0;
    int idx_f_response = 0;
    for (int p : primes) {
        f_response[idx_f_response] = response[idx] - start[idx];
        idx += p;
        idx_f_response++;
    }

    cout << chinese_theorem(primes, f_response, 9) << endl;
    cout.flush();

    return 0;
}



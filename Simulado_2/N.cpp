#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int MAX = 50001;
ll mu[MAX];
ll sum_mu[MAX]; 

void mobius(int n) {
    vector<int> primes;
    vector<bool> is_prime(n + 1, true);
    mu[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (i * p > n) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }
    for (int i = 1; i <= n; i++) sum_mu[i] = sum_mu[i - 1] + mu[i];
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    mobius(MAX - 1);

    int T;
    cin >> T;

    while (T--)
    {
        ll a, b, d;

        cin >> a >> b >> d;

        ll count = 0;
        ll a_div = a / d;
        ll b_div = b / d;
        ll limit = min(a_div, b_div);

        for (ll l = 1, r; l <= limit; l = r + 1) {
            r = min({limit, a_div / (a_div / l), b_div / (b_div / l)});
            
            count += (sum_mu[r] - sum_mu[l - 1]) * (a_div / l) * (b_div / l);
        }

        cout << count << endl;
    }
}
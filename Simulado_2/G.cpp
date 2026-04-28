#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;
const int MAX_PRIME = 1000000;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll N, K;
    cin >> N >> K;

    if (K == 0)
    {
        cout << 1 << endl;
        return 0;
    }

    vector<int> primes;
    vector<bool> is_prime(MAX_PRIME + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p <= MAX_PRIME; p++)
    {
        if (is_prime[p])
        {
            primes.push_back(p);
            for (int i = 2 * p; i <= MAX_PRIME; i += p)
                is_prime[i] = false;
        }
    }

    vector<ll> numerators(K);
    for (ll i = 0; i < K; i++)
    {
        numerators[i] = N - i;
    }

    ll total_divisors = 1;

    for (int p : primes)
    {
        if (p > N)
            break;

        ll exponent_p = 0;

        if (p <= K)
        {
            ll temp_k = K;
            while (temp_k > 0)
            {
                exponent_p -= (temp_k / p);
                temp_k /= p;
            }
        }

        ll start = (N - K + 1 + p - 1) / p * p;
        for (ll m = start; m <= N; m += p)
        {
            ll &val = numerators[N - m];
            while (val % p == 0)
            {
                val /= p;
                exponent_p++;
            }
        }

        if (exponent_p > 0)
        {
            total_divisors = (total_divisors * (exponent_p + 1)) % MOD;
        }
    }

    for (ll val : numerators)
    {
        if (val > 1)
        {
            total_divisors = (total_divisors * 2) % MOD;
        }
    }

    cout << total_divisors << endl;

    return 0;
}
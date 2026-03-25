#include <bits/stdc++.h>

using namespace std;

#define ll long long

vector<ll> mobius(ll n)
{
    vector<ll> mu(n + 1, 0);
    vector<int> primes;
    vector<bool> is_prime(n + 1, true);

    mu[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            mu[i] = -1;
        }

        for (int p : primes)
        {
            if (i * p > n)
                break;

            is_prime[i * p] = false;
            if (i % p == 0)
            {
                mu[i * p] = 0;
                break;        
            }
            else
            {
                mu[i * p] = -mu[i];
            }
        }
    }
    return mu;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<ll> mu = mobius(1000000);

    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;

        ll count_volume = 0;
        ll count_faces = 0;
        for (int d = 1; d <= N; d++)
        {   
            ll div = N / d;
            count_volume += (ll) mu[d] * div * div * div;
            count_faces += (ll) mu[d] * div * div;

        }
        cout << count_volume + 3 * count_faces + 3 << endl;
    }

    return 0;
}
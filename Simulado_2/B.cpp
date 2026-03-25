#include <bits/stdc++.h>

using namespace std;
#define ll long long

// source: https://smsxgz.github.io/post/pe/counting_square_free_numbers/
// mobius function: https://en.wikipedia.org/wiki/M%C3%B6bius_function
vector<ll> mobius(ll n)
{
    vector<bool> is_prime(n + 1, true);
    vector<ll> mobius(n + 1, 1);

    for (ll i = 2; i <= n; i++)
    {
        if (is_prime[i])
        {
            mobius[i] = -1;
        } else {
            continue;
        }

        for (ll j = 2; j <= n / i; j++)
        {
            is_prime[i * j] = false;
            mobius[i * j] *= -1;
        }

        for (ll j = 1; j <= n / (i * i); j++)
        {
            mobius[j * i * i] = 0;
        }
    }

    return mobius;
}

ll count_square_free(ll N)
{
    ll limit = (ll)sqrt(N);
    vector<ll> mu = mobius(limit);

    ll ans = 0;
    for (ll i = 1; i <= limit; i++)
    {
        ans += mu[i] * (N / (i * i));
    }

    return ans;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        ll N;
        cin >> N;
        cout << count_square_free(N) << endl;
    }

    return 0;
}
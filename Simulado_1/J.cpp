#include <bits/stdc++.h>

using namespace std;
#define ll long long

const long long MOD = 1000000007;

ll power(ll base, ll exp)
{
    ll result = 1;
    base = base % MOD;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

ll modInverse(ll n)
{
    return power(n, MOD - 2);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<ll> L(n), Q(n);
    for (int i = 0; i < n; i++)
    {
        cin >> L[i] >> Q[i];
    }

    ll dp = L[n - 1] % MOD;

    for (int i = n - 2; i >= 0; i--)
    {
        ll l = L[i];
        ll q = Q[i];

        ll r_num = (l - 1) % MOD;
        ll r_den = modInverse(l);
        ll r = (r_num * r_den) % MOD;

        ll r_pow_q = power(r, q);

        ll E_atual = (1 - r_pow_q + MOD) % MOD;
        E_atual = (E_atual * l) % MOD;

        dp = (E_atual + (r_pow_q * dp) % MOD) % MOD;
    }

    cout << dp << "\n";

    return 0;
}
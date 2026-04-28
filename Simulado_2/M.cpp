#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

ll calcular_f_pe(ll p, int e)
{
    ll cur_f = 1;
    ll p_mod = p % MOD;
    ll p_pow_odd = p_mod;
    ll p_sq = (p_mod * p_mod) % MOD;

    for (int i = 1; i <= e; ++i)
    {
        // term = p^{2i-1} * (p - 1)
        ll term = (p_pow_odd * (p_mod - 1 + MOD)) % MOD;
        cur_f = (cur_f + term) % MOD;
        // Prepara p^{2i+1} para a proxima iteracao
        p_pow_odd = (p_pow_odd * p_sq) % MOD;
    }
    return cur_f;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll P;
    cin >> P;

    ll M = P - 1;
    ll ans = 1;

    // Fatoracao de P-1 em O(sqrt(P))
    for (ll i = 2; i * i <= M; ++i)
    {
        if (M % i == 0)
        {
            int e = 0;
            while (M % i == 0)
            {
                M /= i;
                e++;
            }
            ans = (ans * calcular_f_pe(i, e)) % MOD;
        }
    }

    if (M > 1)
    {
        ans = (ans * calcular_f_pe(M, 1)) % MOD;
    }


    ans = (ans + 1) % MOD;

    cout << ans << endl;

    return 0;
}
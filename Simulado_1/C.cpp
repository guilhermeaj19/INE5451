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
        {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

ll modInverse(ll n)
{
    return power(n, MOD-2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, T;
    cin >> n >> T;

    if (T > n) {
        cout << 0 << endl;
        return 0;
    }

    vector<ll> fact(n + 1, 1);
    vector<ll> invFact(n + 1, 1);

    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    invFact[n] = modInverse(fact[n]);
    for (int i = n - 1; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    vector<ll> dp(n + 1, 0);
    ll current_sum = 0;

    for (int i = T; i <= n; i++) {
        if (i > T) {
            ll term_add = (dp[i-1] * invFact[i-1]) % MOD;
            current_sum = (current_sum + term_add) % MOD;

            ll term_sub = (dp[i-T] * invFact[i-T]) % MOD;
            current_sum = (current_sum - term_sub + MOD) % MOD;

        }

        ll part1 = fact[i-1]*current_sum % MOD;
        ll part2 = (1LL * (i-T+1) * fact[i-1]) % MOD;
        dp[i] = (part1 + part2) % MOD;
    }

    cout << dp[n] << endl;

    return 0;
}
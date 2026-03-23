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
    ll k,n;

    cin >> k >> n;

    vector<ll> fact(n + 1, 1);
    vector<ll> invFact(n + 1, 1);

    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    invFact[n] = modInverse(fact[n]);
    for (int i = n - 1; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }


    ll current_sum = 0;

    for (int i = 0; i <= n; i++) {
        ll aux = 0;
        aux = power(i, k) * invFact[i] % MOD;
        aux = (aux * invFact[n-i]) % MOD;

        if ((n-i) % 2 != 0) {
            aux *= -1;
        }
        aux = (aux + MOD) % MOD;

        current_sum = (current_sum + aux) % MOD;
    }

    cout << fact[n] * current_sum % MOD << endl;

}
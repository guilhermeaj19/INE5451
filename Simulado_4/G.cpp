#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll MOD = 998244353;
ll MAXN = 200005;

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
    return power(n, MOD - 2);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<ll> fact(MAXN + 1, 1);

    for (int i = 1; i <= MAXN; i++)
    {
        fact[i] = (fact[i - 1] * i) % MOD;
    }


    int T;
    cin >> T;

    while (T--)
    {

        int n;
        cin >> n;
        vector<int> a(n);

        for (int &x : a)
        {
            cin >> x;
        }

        int max = *max_element(a.begin(), a.end());
        int c_max = count(a.begin(), a.end(), max);
        int k = count(a.begin(), a.end(), max - 1);

        if (k == 0 && c_max == 1) {
            cout << 0 << "\n";
            continue;
        }

        ll first = fact[n];
        if (c_max == 1) {
            ll second = (fact[n] * modInverse(k + 1))  % MOD;
            cout << (first - second + MOD) % MOD << "\n";
        }
            
        else cout << first << "\n";
    }
}
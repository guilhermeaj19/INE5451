#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;

    ll mod = 1000000007;
    ll inv2 = 500000004;
    ll total_sum = 0;

    for (ll l = 1, r; l <= n; l = r + 1)
    {
        ll k = n / l;
        r = n / k;
        if (r > n)
            r = n;

        ll num_terms = (r - l + 1) % mod;
        ll sum_interval = ((l + r) % mod * num_terms) % mod;
        sum_interval = (sum_interval * inv2) % mod;

        ll contrib_block = (sum_interval * (k % mod)) % mod;
        total_sum = (total_sum + contrib_block) % mod;
    }

    cout << total_sum << endl;

    return 0;
}
#include <bits/stdc++.h>

using namespace std;
#define ll long long


ll count_divisors(ll n) {
    ll ans = 0;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ans += i; // divisor i
            if (i != n / i) {
                ans += n / i; // divisor n/i
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll N;
    cin >> N;

    ll MOD = 1000000007;

    ll ans = 0;

    for (int i = 1; i <= N; i++) {
        ll count = count_divisors(i);
        // cout << "Number: " << i << ", Divisors: " << count << endl;
        ans = (ans + count) % MOD;
    }

    cout << ans << endl;


    return 0;
}
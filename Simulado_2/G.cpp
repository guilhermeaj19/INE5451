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
    ll a, b, c, d;
    gcd(a,b,c,d);
    return ans;
}

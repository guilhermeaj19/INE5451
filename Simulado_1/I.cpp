#include <bits/stdc++.h>

using namespace std;
#define ll long long

const long long MOD = 1000000007;

int main() {
    ll k,n;

    cin >> n >> k;

    if (n==1 && k==1) {
        cout << 1 << endl;
        return 0;
    }

    if (k * 2 > n) {
        cout << 0 << endl;
        return 0;
    }

    long long ans = n;
    for (long long i = 0; i < k - 1; i++) {
        ans = (ans * (n - k - 1 - i)) % MOD;
    }
    cout << ans << endl;
    return 0;
}
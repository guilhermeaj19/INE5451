#include <bits/stdc++.h>

using namespace std;

long long MAX = 1000000007;

// unsigned nChoosek(unsigned n, unsigned k )
// {
//     if (k > n) return 0;
//     if (k * 2 > n) k = n-k;
//     if (k == 0) return 1;

//     int result = n;
//     for( int i = 2; i <= k; ++i ) {
//         result = (result * (n-i+1)) % MAX;
//         result = (result/i) % MAX;
//     }
//     return result;
// }


int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
    // n--;
  
    int result = 1;

    for (int i = 1; i < n; i++) {
        result = result*2 % MAX;
    }

    // for (int i = 0; i < n/31; i++) {
    //     result = (result << 31) % MAX;
    // }

    // if (n % 31 != 0) {
    //     result = (1 << (n % 31)) % MAX;
    // }
    cout << result << endl;
    return 0;
}
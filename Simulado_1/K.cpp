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



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, a, b;
    cin >> R >> a >> b;

    int N = R;
    vector<vector<ll>> mat(N, vector<ll>(N + 1, 0));

    for (int i = 0; i < N; i++) {
        mat[i][i] = R; 
        mat[i][N] = R; 

        for (int j = 1; j <= R - 1 - i; j++) {
            int nxt = (1LL * (i + j) * (b - a)) / b; 
            
            mat[i][nxt] = (mat[i][nxt] - 1 + MOD) % MOD;
        }
    }

    for (int i = 0; i < N; i++) {
        int pivot = i;
        for (int j = i; j < N; j++) {
            if (mat[j][i] != 0) {
                pivot = j;
                break;
            }
        }
        
        swap(mat[i], mat[pivot]);

        ll inv = modInverse(mat[i][i]);
        for (int j = i; j <= N; j++) {
            mat[i][j] = (mat[i][j] * inv) % MOD;
        }

        for (int j = 0; j < N; j++) {
            if (i != j && mat[j][i] != 0) {
                ll factor = mat[j][i];
                for (int k = i; k <= N; k++) {
                    mat[j][k] = (mat[j][k] - factor * mat[i][k]) % MOD;
                    if (mat[j][k] < 0) mat[j][k] += MOD;
                }
            }
        }
    }

    cout << mat[0][N] << "\n";

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000;
int phi[MAXN + 1];
int prefix_phi_sum[MAXN + 1];

void precompute() {
    for (int i = 0; i <= MAXN; i++) phi[i] = i;

    for (int i = 2; i <= MAXN; i++) {
        if (phi[i] == i) { // i é primo
            for (int j = i; j <= MAXN; j += i)
                phi[j] -= phi[j] / i;
        }
    }

    prefix_phi_sum[0] = 0;
    for (int i = 1; i <= MAXN; i++) {
        prefix_phi_sum[i] = prefix_phi_sum[i - 1] + phi[i];
    }
}

int main() {
    precompute();

    int C;
    cin >> C;

    for (int t = 1; t <= C; t++) {
        int N;
        cin >> N; 

        int result = 3 + 2 * (prefix_phi_sum[N] - prefix_phi_sum[1]);

        cout << t << " " << N << " " << result << endl;
    }

    return 0;
}
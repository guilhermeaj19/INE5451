#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int MAX = 1000005;
ll phi[MAX];
ll phi_prefix[MAX];

void precompute_phi()
{
    for (int i = 0; i < MAX; i++)
    {
        phi[i] = i;
    }

    for (int i = 2; i < MAX; i++)
    {
        if (phi[i] == i)
        {
            for (int j = i; j < MAX; j += i)
            {
                phi[j] -= phi[j] / i;
            }
        }
    }

    phi_prefix[0] = 0;
    for (int i = 1; i < MAX; i++)
    {
        phi_prefix[i] = phi_prefix[i - 1] + phi[i];
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute_phi();

    ll N;
    ll count, total_sum, val_n_t, l, r, current_phi_sum;
    
    while (cin >> N && N != 0)
    {
        total_sum = 0;

        for (l = 1, r; l <= N && l <= N; l = r + 1)
        {
            val_n_t = N / l;

            r = N / val_n_t;
 
            count = (val_n_t * (val_n_t - 1)) / 2;

            current_phi_sum = phi_prefix[r] - phi_prefix[l - 1];

            total_sum += count * current_phi_sum;
        }

        cout << total_sum << "\n";
    }

    return 0;
}
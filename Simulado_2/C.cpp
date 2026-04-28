#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1000001;
ll phi[MAX];
ll f[MAX];
ll G[MAX];

void precompute()
{
    for (int i = 0; i < MAX; i++)
        phi[i] = i;
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

    for (int d = 1; d < MAX; d++)
    {
        for (int n = 2 * d; n < MAX; n += d)
        {
            f[n] += (ll)d * phi[n / d];
        }
    }

    G[0] = 0;
    G[1] = 0;
    for (int i = 2; i < MAX; i++)
    {
        G[i] = G[i - 1] + f[i];
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int N;
    while (cin >> N && N != 0)
    {
        cout << G[N] << "\n";
    }

    return 0;
}
#include <bits/stdc++.h>

using namespace std;
#define ll long long

ll solve(ll N)
{
    vector<ll> phi(N + 1);
    for (ll i = 0; i <= N; i++)
    {
        phi[i] = i;
    }

    for (ll i = 2; i <= N; i++)
    {
        if (phi[i] == i)
        {
            for (ll j = i; j <= N; j += i)
            {

                phi[j] -= phi[j] / i;
            }
        }
    }

    vector<ll> S(N + 1, 0);
    for (ll i = 2; i <= N; i++)
    {

        S[i] = S[i - 1] + phi[i];
    }

    ll G = 0;
    for (ll g = 1; g <= N; g++)
    {
        G += (ll)g * S[N / g];
    }
    return G;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll N;
    while (cin >> N && N != 0)
    {
        cout << solve(N) << endl;
    }

    return 0;
}
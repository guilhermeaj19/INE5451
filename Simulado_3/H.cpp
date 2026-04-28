#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;

        vector<ll> a(n), b(m);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < m; i++)
            cin >> b[i];

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        vector<ll> diffA, diffB;
        for (int i = 0; i < n / 2; i++)
        {
            diffA.push_back(a[n - 1 - i] - a[i]);
        }
        for (int i = 0; i < m / 2; i++)
        {
            diffB.push_back(b[m - 1 - i] - b[i]);
        }

        vector<ll> prefA(diffA.size() + 1, 0), prefB(diffB.size() + 1, 0);
        for (int i = 0; i < diffA.size(); i++)
            prefA[i + 1] = prefA[i] + diffA[i];
        for (int i = 0; i < diffB.size(); i++)
            prefB[i + 1] = prefB[i] + diffB[i];

        vector<pair<ll, int>> merged;
        for (ll v : diffA)
            merged.push_back({v, 0});
        for (ll v : diffB)
            merged.push_back({v, 2});
        sort(merged.rbegin(), merged.rend());

        vector<int> x_best_at_k(n + m + 1, 0);
        int current_x = 0;
        for (int k = 1; k <= (int)merged.size(); k++)
        {
            if (merged[k - 1].second == 0)
                current_x++;
            x_best_at_k[k] = current_x;
        }

        for (int k = merged.size() + 1; k <= n + m; k++)
            x_best_at_k[k] = current_x;

        int k_max = 0;
        vector<ll> results;
        for (int k = 1;; k++)
        {

            int low = max(0, 2 * k - m);
            int high = min(k, n - k);

            if (low > high)
                break;

            k_max = k;

            int x_opt = max(low, min(high, x_best_at_k[k]));

            ll score = prefA[x_opt] + prefB[k - x_opt];
            results.push_back(score);
        }

        cout << k_max << "\n";
        for (int i = 0; i < results.size(); i++)
        {
            cout << results[i] << (i == results.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
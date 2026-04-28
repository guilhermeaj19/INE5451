#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;

        vector<pair<int, int>> problems(n);
        vector<ll> countTopic(n + 1, 0);
        vector<ll> countDiff(n + 1, 0);

        for (int i = 0; i < n; i++)
        {
            cin >> problems[i].first >> problems[i].second;
            countTopic[problems[i].first]++;
            countDiff[problems[i].second]++;
        }

        // total = (n 3)
        ll total_combinations = n * (n - 1) * (n - 2) / 6;

        ll bad_sets = 0;
        for (int i = 0; i < n; i++)
        {
            ll same_topic = countTopic[problems[i].first] - 1;
            ll same_diff = countDiff[problems[i].second] - 1;

            bad_sets += same_topic * same_diff;
        }

        cout << total_combinations - bad_sets << "\n";
    }
    return 0;
}
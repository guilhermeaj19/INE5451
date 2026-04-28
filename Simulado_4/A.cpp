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
        int n;
        cin >> n;
        map<ll, int> freq;
        for (int i = 0; i < n; i++)
        {
            ll a;
            cin >> a;
            freq[a]++;
        }

        vector<ll> pairs;
        vector<ll> top_singles;
        ll current_pair_sum = 0;

        for (auto it = freq.rbegin(); it != freq.rend(); ++it)
        {
            ll val = it->first;
            int count = it->second;

            int num_p = count / 2;
            for (int i = 0; i < num_p; i++)
            {
                pairs.push_back(val);
                current_pair_sum += 2 * val;
            }
            if (count % 2 == 1)
            {
                top_singles.push_back(val);
            }
        }

        sort(top_singles.begin(), top_singles.end(), greater<ll>());
        if (top_singles.size() > 2)
            top_singles.resize(2);

        ll max_p = 0;

        for (int i = 0; i < (int)pairs.size(); i++)
        {
            ll L_max_p = pairs[i];

            if (pairs.size() - i >= 2)
            {
                if (2 * L_max_p < current_pair_sum)
                {
                    max_p = max(max_p, current_pair_sum);
                }
            }

            if (!top_singles.empty())
            {
                ll s1 = top_singles[0];
                ll total = current_pair_sum + s1;
                if (2 * max(L_max_p, s1) < total)
                {
                    max_p = max(max_p, total);
                }
            }

            if (top_singles.size() >= 2)
            {
                ll s1 = top_singles[0];
                ll s2 = top_singles[1];
                ll total = current_pair_sum + s1 + s2;
                if (2 * max(L_max_p, s1) < total)
                {
                    max_p = max(max_p, total);
                }
            }

            current_pair_sum -= 2 * pairs[i];
            top_singles.push_back(pairs[i]);
            top_singles.push_back(pairs[i]);
            sort(top_singles.begin(), top_singles.end(), greater<ll>());
            if (top_singles.size() > 2)
                top_singles.resize(2);
        }

        cout << max_p << endl;
    }
    return 0;
}
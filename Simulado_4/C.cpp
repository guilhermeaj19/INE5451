#include <bits/stdc++.h>

using namespace std;

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

        int min_sum = INT_MAX, max_sum = INT_MIN;
        int min_diff = INT_MAX, max_diff = INT_MIN;

        for (int i = 1; i <= n; ++i)
        {
            string row;
            cin >> row;
            for (int j = 1; j <= m; ++j)
            {
                if (row[j - 1] == 'B')
                {
                    min_sum = min(min_sum, i + j);
                    max_sum = max(max_sum, i + j);
                    min_diff = min(min_diff, i - j);
                    max_diff = max(max_diff, i - j);
                }
            }
        }

        int best_dist = INT_MAX;
        int ans_a = 1, ans_b = 1;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                int current_max_dist = max({abs((i + j) - min_sum),
                                            abs((i + j) - max_sum),
                                            abs((i - j) - min_diff),
                                            abs((i - j) - max_diff)});

                if (current_max_dist < best_dist)
                {
                    best_dist = current_max_dist;
                    ans_a = i;
                    ans_b = j;
                }
            }
        }

        cout << ans_a << " " << ans_b << endl;
    }
    return 0;
}
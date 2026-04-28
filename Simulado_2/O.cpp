#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000001;
int super_cnt[MAXN];

void solve()
{
    int n;
    cin >> n;

    fill(super_cnt, super_cnt + MAXN, 0);

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        super_cnt[a[i]]++;
    }

    for (int i = 0; i < 20; i++)
    {
        for (int mask = 0; mask < MAXN; mask++)
        {
            if (!(mask & (1 << i)))
            {
                int next_mask = mask | (1 << i);
                if (next_mask < MAXN)
                {
                    super_cnt[mask] += super_cnt[next_mask];
                }
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += super_cnt[a[i]];
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int z;
    cin >> z;
    while (z--)
    {
        solve();
    }
    return 0;
}
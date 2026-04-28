#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll scan(int r, int c)
{
    cout << "SCAN " << r << " " << c << endl;
    ll res;
    cin >> res;
    return res;
}

int dig(int r, int c)
{
    cout << "DIG " << r << " " << c << endl;
    int res;
    cin >> res;
    return res;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;

        ll s1 = scan(1, 1);
        ll s2 = scan(1, m);

        // s1 = (r1-1) + (r2-1) + (c1-1) + (c2-1)
        // rs + cs - 4 = s1
        // rs + cs = s1 + 4
        ll rs_plus_cs = s1 + 4;

        // s2 = (r1-1) + (r2-1) + (m-c1) + (m-c2)
        // rs - cs + 2m - 2 = s2
        // rs - cs = s2 - 2m + 2
        ll rs_minus_cs = s2 - 2 * m + 2;

        // rs + cs = s1 + 4
        // rs - cs = s2 - 2m + 2
        int rs = (rs_plus_cs + rs_minus_cs) / 2;
        int cs = rs_plus_cs - rs;

        int midR = rs / 2;
        ll s3 = scan(midR, 1);

        // s3 = (midR - r1) + (r2 - midR) + (c1-1) + (c2-1)
        // s3 = (r2 - r1) + cs - 2
        // dr = (r2 - r1) = s3 - (cs - 2)
        // r1 + r2 = rs
        // r2 - r1 = dr
        int dr = s3 - (cs - 2);
        int r1 = (rs - dr) / 2;
        int r2 = (rs + dr) / 2;

        int midC = cs / 2;
        ll s4 = scan(1, midC);

        // s4 = (r1-1) + (r2-1) + (midC - c1) + (c2 - midC)
        // s4 = rs - 2 + (c2 - c1)
        // dc = (c2 - c1) = s4 - (rs - 2)
        // c1 + c2 = cs
        // c2 - c1 = dc

        int dc = s4 - (rs - 2);
        int c1 = (cs - dc) / 2;
        int c2 = (cs + dc) / 2;

        if (dig(r1, c1))
        {
            dig(r2, c2);
        }
        else
        {
            dig(r1, c2);
            dig(r2, c1);
        }
    }
    return 0;
}
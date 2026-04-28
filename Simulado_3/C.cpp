#include <bits/stdc++.h>
using namespace std;


const double PI = acos(-1.0);

struct Star
{
    int x, y, b;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<Star> stars(N);
    for (int i = 0; i < N; ++i)
        cin >> stars[i].x >> stars[i].y >> stars[i].b;

    vector<double> angles;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (stars[i].b > stars[j].b)
            {
                angles.push_back(atan2(stars[i].y - stars[j].y, stars[i].x - stars[j].x));
            }
        }
    }

    if (angles.empty())
    {
        cout << "Y" << endl;
        return 0;
    }

    sort(angles.begin(), angles.end());

    double max_gap = 0;
    int m = angles.size();
    for (int i = 0; i < m - 1; ++i)
    {
        max_gap = max(max_gap, angles[i + 1] - angles[i]);
    }
    max_gap = max(max_gap, 2.0 * PI - (angles.back() - angles[0]));

    if (max_gap >= PI - 1e-9)
    {
        cout << "Y" << endl;
    }
    else
    {
        cout << "N" << endl;
    }

    return 0;
}
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point
{
    int x, y, id;
    bool isLeft = false;
    bool isBottom = false;
};

void solve()
{
    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
        points[i].id = i + 1;
    }

    sort(points.begin(), points.end(), [](const Point &a, const Point &b) { return a.x < b.x; });
    for (int i = 0; i < n / 2; i++) points[i].isLeft = true;

    sort(points.begin(), points.end(), [](const Point &a, const Point &b) { return a.y < b.y; });
    for (int i = 0; i < n / 2; i++) points[i].isBottom = true;

    vector<int> Left_Bottom, Left_Top, Right_Bottom, Right_Top;
    for (int i = 0; i < n; i++)
    {
        if (points[i].isLeft && points[i].isBottom)
            Left_Bottom.push_back(points[i].id);
        else if (points[i].isLeft && !points[i].isBottom)
            Left_Top.push_back(points[i].id);
        else if (!points[i].isLeft && points[i].isBottom)
            Right_Bottom.push_back(points[i].id);
        else
            Right_Top.push_back(points[i].id);
    }

    for (size_t i = 0; i < Left_Bottom.size(); i++)
    {
        cout << Left_Bottom[i] << " " << Right_Top[i] << "\n";
    }
    for (size_t i = 0; i < Left_Top.size(); i++)
    {
        cout << Left_Top[i] << " " << Right_Bottom[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        solve();
    }
}
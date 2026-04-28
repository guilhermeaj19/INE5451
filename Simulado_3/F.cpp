#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const ld EPS = 1e-12;

struct Point
{
    ld x, y;
    bool operator<(const Point &o) const
    {
        return x < o.x || (abs(x - o.x) < EPS && y < o.y);
    }
};

ld cross_product(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

ld dot_product(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}

ld distSq(Point a, Point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

vector<Point> get_convex_hull(vector<Point> &pts)
{
    int n = pts.size(), k = 0;
    if (n <= 2)
        return pts;

    vector<Point> h(2 * n);
    sort(pts.begin(), pts.end());
    for (int i = 0; i < n; ++i)
    {
        while (k >= 2 && cross_product(h[k - 2], h[k - 1], pts[i]) <= 0)
            k--;
        h[k++] = pts[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--)
    {
        while (k >= t && cross_product(h[k - 2], h[k - 1], pts[i]) <= 0)
            k--;
        h[k++] = pts[i];
    }
    h.resize(k - 1);
    return h;
}

Point rotate(Point p, ld cos_t, ld sin_t)
{
    return {p.x * cos_t - p.y * sin_t, p.x * sin_t + p.y * cos_t};
}

int main()
{
    int n;
    cin >> n;

    vector<Point> pts(n);
    for (int i = 0; i < n; i++)
        cin >> pts[i].x >> pts[i].y;

    vector<Point> hull = get_convex_hull(pts);
    int m = hull.size();

    ld minArea = 1e30;
    vector<Point> bestRect(4);

    for (int i = 0; i < m; i++)
    {
        Point p1 = hull[i];
        Point p2 = hull[(i + 1) % m];

        ld dx = p2.x - p1.x;
        ld dy = p2.y - p1.y;
        ld angle = atan2(dy, dx);

        ld cos_t = cos(-angle);
        ld sin_t = sin(-angle);

        ld minX = 1e30, maxX = -1e30, minY = 1e30, maxY = -1e30;

        for (const auto &p : hull)
        {
            Point rp = rotate(p, cos_t, sin_t);
            minX = min(minX, rp.x);
            maxX = max(maxX, rp.x);
            minY = min(minY, rp.y);
            maxY = max(maxY, rp.y);
        }

        ld area = (maxX - minX) * (maxY - minY);
        if (area < minArea)
        {
            minArea = area;

            vector<Point> corners = {
                {maxX, minY}, {maxX, maxY}, {minX, maxY}, {minX, minY}};

            ld cos_inv = cos(angle);
            ld sin_inv = sin(angle);
            for (int j = 0; j < 4; j++)
            {
                bestRect[j] = rotate(corners[j], cos_inv, sin_inv);
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        printf("%.10Lf %.10Lf\n", bestRect[i].x, bestRect[i].y);
    }

    return 0;
}
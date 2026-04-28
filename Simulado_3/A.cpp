#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pt
{
    ll x, y;
    pt operator+(const pt &p) const { return {x + p.x, y + p.y}; }
    pt operator-(const pt &p) const { return {x - p.x, y - p.y}; }
    ll cross(const pt &p) const { return x * p.y - y * p.x; }
    ll cross(const pt &a, const pt &b) const { return (a - *this).cross(b - *this); }
};

vector<pt> convex_hull(vector<pt> a)
{
    if (a.size() <= 2)
        return a;
    sort(a.begin(), a.end(), [](pt p1, pt p2)
         { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); });
    vector<pt> up, down;
    for (auto p : a)
    {
        while (up.size() >= 2 && up[up.size() - 2].cross(up.back(), p) >= 0)
            up.pop_back();
        up.push_back(p);
        while (down.size() >= 2 && down[down.size() - 2].cross(down.back(), p) <= 0)
            down.pop_back();
        down.push_back(p);
    }
    a.clear();
    for (int i = 0; i < (int)down.size() - 1; i++)
        a.push_back(down[i]);
    for (int i = (int)up.size() - 1; i > 0; i--)
        a.push_back(up[i]);
    return a;
}

void reorder_polygon(vector<pt> &P)
{
    size_t pos = 0;
    for (size_t i = 1; i < P.size(); i++)
    {
        if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<pt> minkowski(vector<pt> P, vector<pt> Q)
{
    reorder_polygon(P);
    reorder_polygon(Q);
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    vector<pt> res;
    size_t i = 0, j = 0;
    while (i < P.size() - 2 || j < Q.size() - 2)
    {
        res.push_back(P[i] + Q[j]);
        ll c = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if (c >= 0 && i < P.size() - 2)
            ++i;
        if (c <= 0 && j < Q.size() - 2)
            ++j;
    }
    return convex_hull(res);
}

bool is_inside(const vector<pt> &poly, pt p)
{
    int n = poly.size();
    if (n < 3)
        return false;
    if (poly[0].cross(poly[1], p) < 0 || poly[0].cross(poly[n - 1], p) > 0)
        return false;

    int l = 1, r = n - 1;
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (poly[0].cross(poly[mid], p) >= 0)
            l = mid;
        else
            r = mid;
    }
    return poly[l].cross(poly[r], p) >= 0;
}

vector<pt> prepare_poly(vector<pt> p, int scale)
{
    for (auto &v : p)
    {
        v.x *= scale;
        v.y *= scale;
    }

    return p;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int M1, M2, N;

    auto read_poly = [&](int k)
    {
        vector<pt> p(k);
        for (int i = 0; i < k; i++)
            cin >> p[i].x >> p[i].y;
        return p;
    };

    if (!(cin >> M1))
        return 0;
    vector<pt> A = read_poly(M1);

    cin >> M2;
    vector<pt> B = read_poly(M2);

    // Caso 1: 2M = P1 + P2
    vector<pt> sum1 = minkowski(A, B);
    // Caso 2: M = 2P1 - P2
    vector<pt> sum2 = minkowski(prepare_poly(A, 2), prepare_poly(B, -1));
    // Caso 3: M = 2P2 - P1
    vector<pt> sum3 = minkowski(prepare_poly(B, 2), prepare_poly(A, -1));

    cin >> N;
    string res = "";
    for (int i = 0; i < N; i++)
    {
        pt p;
        cin >> p.x >> p.y;
        if (is_inside(sum1, {p.x * 2, p.y * 2}) || is_inside(sum2, p) || is_inside(sum3, p))
        {
            res += 'Y';
        }
        else
        {
            res += 'N';
        }
    }
    cout << res << "\n";

    return 0;
}
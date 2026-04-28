#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Rect
{
    int h, w, id;
};

bool check(ll H, ll W, int n, const vector<Rect> &byH, const vector<Rect> &byW)
{
    vector<bool> used(n, false);
    int ptrH = 0, ptrW = 0;
    int count = 0;

    while (count < n)
    {
        bool found = false;

        while (ptrH < n && (used[byH[ptrH].id] || byH[ptrH].h > H))
            ptrH++;

        ll width_sum = 0;
        bool gotH = false;
        while (ptrH < n && byH[ptrH].h == H)
        {
            if (!used[byH[ptrH].id])
            {
                width_sum += byH[ptrH].w;
                used[byH[ptrH].id] = true;
                gotH = true;
                count++;
            }
            ptrH++;
        }
        if (gotH)
        {
            W -= width_sum;
            found = true;
        }

        while (ptrW < n && (used[byW[ptrW].id] || byW[ptrW].w > W))
            ptrW++;

        ll height_sum = 0;
        bool gotW = false;
        while (ptrW < n && byW[ptrW].w == W)
        {
            if (!used[byW[ptrW].id])
            {
                height_sum += byW[ptrW].h;
                used[byW[ptrW].id] = true;
                gotW = true;
                count++;
            }
            ptrW++;
        }
        if (gotW)
        {
            H -= height_sum;
            found = true;
        }

        if (!found)
            break;
    }

    return (count == n);
}

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
        vector<Rect> rects(n);
        ll total_area = 0;
        int max_h = 0, max_w = 0;

        for (int i = 0; i < n; i++)
        {
            cin >> rects[i].h >> rects[i].w;
            rects[i].id = i;
            total_area += (ll)rects[i].h * rects[i].w;
            max_h = max(max_h, rects[i].h);
            max_w = max(max_w, rects[i].w);
        }

        vector<Rect> byH = rects;
        vector<Rect> byW = rects;
        sort(byH.begin(), byH.end(), [](Rect a, Rect b)
             { return a.h > b.h; });
        sort(byW.begin(), byW.end(), [](Rect a, Rect b)
             { return a.w > b.w; });

        set<pair<ll, ll>> results;

        if (total_area % max_h == 0)
        {
            if (check(max_h, total_area / max_h, n, byH, byW))
            {
                results.insert({(ll)max_h, total_area / max_h});
            }
        }

        if (total_area % max_w == 0)
        {
            if (check(total_area / max_w, max_w, n, byH, byW))
            {
                results.insert({total_area / max_w, (ll)max_w});
            }
        }

        cout << results.size() << "\n";
        for (auto p : results)
        {
            cout << p.first << " " << p.second << "\n";
        }
    }
    return 0;
}
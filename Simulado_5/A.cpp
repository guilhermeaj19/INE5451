#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct SAM
{
    struct Node
    {
        int len, link;
        int next[26];
    } st[MAXN * 2];
    int sz, last;

    void init()
    {
        for (int i = 0; i < MAXN * 2; ++i)
        {
            st[i].len = 0;
            st[i].link = -1;
            for (int j = 0; j < 26; ++j)
                st[i].next[j] = 0;
        }
        sz = 1;
        last = 0;
    }

    void extend(int c)
    {
        if (st[last].next[c])
        {
            int p = last, q = st[p].next[c];
            if (st[p].len + 1 == st[q].len)
                last = q;
            else
            {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].link = st[q].link;
                for (int i = 0; i < 26; ++i)
                    st[clone].next[i] = st[q].next[i];
                while (p != -1 && st[p].next[c] == q)
                {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = last = clone;
            }
            return;
        }
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next[c])
        {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1)
            st[cur].link = 0;
        else
        {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len)
                st[cur].link = q;
            else
            {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                for (int i = 0; i < 26; ++i)
                    st[clone].next[i] = st[q].next[i];
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[c] == q)
                {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
} sam;

int treeL[MAXN * 4], treeJ[MAXN * 4];

void update(int *tree, int node, int start, int end, int l, int r, int val)
{
    if (l > end || r < start)
        return;
    if (l <= start && end <= r)
    {
        tree[node] = max(tree[node], val);
        return;
    }
    int mid = (start + end) / 2;
    update(tree, 2 * node, start, mid, l, r, val);
    update(tree, 2 * node + 1, mid + 1, end, l, r, val);
}

int query(int *tree, int node, int start, int end, int idx)
{
    int res = tree[node];
    if (start == end)
        return res;
    int mid = (start + end) / 2;
    if (idx <= mid)
        res = max(res, query(tree, 2 * node, start, mid, idx));
    else
        res = max(res, query(tree, 2 * node + 1, mid + 1, end, idx));
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;

    string A;
    cin >> A;
    sam.init();

    for (int i = 0; i < M; ++i)
    {
        string s;
        cin >> s;
        sam.last = 0;
        for (char c : s)
            sam.extend(c - 'a');
    }

    string AA = A + A;
    int v = 0, cur_l = 0;
    for (int j = 0; j < 2 * N; ++j)
    {
        int c = AA[j] - 'a';
        while (v != 0 && !sam.st[v].next[c])
        {
            v = sam.st[v].link;
            cur_l = sam.st[v].len;
        }
        if (sam.st[v].next[c])
        {
            cur_l++;
            v = sam.st[v].next[c];
        }
        else
        {
            v = 0;
            cur_l = 0;
        }
        int Lj = min(cur_l, N);
        if (Lj == 0)
            continue;
        int start_pos = j - Lj + 1;

        int l1 = max(0, j - N + 1), r1 = min(N - 1, start_pos);
        if (l1 <= r1)
            update(treeL, 1, 0, N - 1, l1, r1, Lj);
        

        int l2 = max(0, start_pos + 1), r2 = min(N - 1, j);
        if (l2 <= r2)
            update(treeJ, 1, 0, N - 1, l2, r2, j + 1);
    }

    int ans = N;
    for (int i = 0; i < N; ++i)
    {
        int score = max(query(treeL, 1, 0, N - 1, i), query(treeJ, 1, 0, N - 1, i) - i);
        ans = min(ans, score);
    }
    cout << ans << endl;
    return 0;
}
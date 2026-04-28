#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("O3,unroll-loops")

int trie[2005][26];
int trans[2005][26];
int fail[2005];
int sc[2005];
int nodes = 1;

void insert(const string &p)
{
    int u = 0;
    for (char c : p)
    {
        int v = c - 'a';
        if (!trie[u][v])
            trie[u][v] = nodes++;
        u = trie[u][v];
    }
    sc[u]++;
}

void build()
{
    queue<int> q;
    for (int i = 0; i < 26; ++i)
    {
        if (trie[0][i])
        {
            trans[0][i] = trie[0][i];
            q.push(trie[0][i]);
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        sc[u] += sc[fail[u]];
        for (int i = 0; i < 26; ++i)
        {
            if (trie[u][i])
            {
                fail[trie[u][i]] = trans[fail[u]][i];
                trans[u][i] = trie[u][i];
                q.push(trie[u][i]);
            }
            else
            {
                trans[u][i] = trans[fail[u]][i];
            }
        }
    }
}

int pre_st[2005];
int pre_sc[2005];
int suf_sc[2005][2005];
int s_idx[2005];
int R[2005];

short jump_table[12][2005][2005];
int score_jump[12][2005][2005];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s))
        return 0;
    int n = s.length();
    for (int i = 0; i < n; ++i)
    {
        s_idx[i] = s[i] - 'a';
        R[n - 1 - i] = s_idx[i];
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        string p;
        cin >> p;
        insert(p);
    }

    build();

    int u = 0;
    pre_st[0] = 0;
    pre_sc[0] = 0;
    for (int i = 0; i < n; ++i)
    {
        u = trans[u][s_idx[i]];
        pre_st[i + 1] = u;
        pre_sc[i + 1] = pre_sc[i] + sc[u];
    }

    for (int j = n; j >= 0; --j)
    {
        for (int i = 0; i < nodes; ++i)
        {
            if (j == n)
            {
                suf_sc[i][j] = 0;
            }
            else
            {
                int nxt = trans[i][s_idx[j]];
                suf_sc[i][j] = sc[nxt] + suf_sc[nxt][j + 1];
            }
        }
    }

    for (int k = 0; k < n; ++k)
    {
        for (int v = 0; v < nodes; ++v)
        {
            int nxt = trans[v][R[k]];
            jump_table[0][k][v] = nxt;
            score_jump[0][k][v] = sc[nxt];
        }
    }

    for (int p = 1; p <= 11; ++p)
    {
        int len = 1 << (p - 1);
        for (int k = 0; k + (1 << p) <= n; ++k)
        {
            for (int v = 0; v < nodes; ++v)
            {
                int nxt1 = jump_table[p - 1][k][v];
                jump_table[p][k][v] = jump_table[p - 1][k + len][nxt1];
                score_jump[p][k][v] = score_jump[p - 1][k][v] + score_jump[p - 1][k + len][nxt1];
            }
        }
    }

    int ans = suf_sc[0][0];

    for (int l = 0; l < n; ++l)
    {
        for (int r = l; r < n; ++r)
        {
            int i = n - 1 - r;
            int j = n - 1 - l;
            int len = j - i + 1;
            int curr = pre_st[l];
            int sum = 0;
            int k = i;

            for (int p = 11; p >= 0; --p)
            {
                if (len >= (1 << p))
                {
                    sum += score_jump[p][k][curr];
                    curr = jump_table[p][k][curr];
                    k += (1 << p);
                    len -= (1 << p);
                }
            }

            int res = pre_sc[l] + sum + suf_sc[curr][r + 1];
            if (res > ans)
                ans = res;
        }
    }

    cout << ans << "\n";
    return 0;
}
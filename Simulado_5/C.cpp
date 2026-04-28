#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b)
{
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

vector<int> build_sa(const vector<int> &s, int n, int k_limit)
{
    int m = max(n, k_limit) + 1;
    vector<int> sa(n), x(n), y(n), c(m, 0);

    for (int i = 0; i < n; i++)
        c[x[i] = s[i]]++;
    for (int i = 1; i < m; i++)
        c[i] += c[i - 1];
    for (int i = n - 1; i >= 0; i--)
        sa[--c[x[i]]] = i;

    for (int k = 1; k < n; k <<= 1)
    {
        int p = 0;
        for (int i = n - k; i < n; i++)
            y[p++] = i;
        for (int i = 0; i < n; i++)
            if (sa[i] >= k)
                y[p++] = sa[i] - k;

        fill(c.begin(), c.end(), 0);
        for (int i = 0; i < n; i++)
            c[x[y[i]]]++;
        for (int i = 1; i < m; i++)
            c[i] += c[i - 1];
        for (int i = n - 1; i >= 0; i--)
            sa[--c[x[y[i]]]] = y[i];

        swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && (sa[i - 1] + k < n ? y[sa[i - 1] + k] : -1) == (sa[i] + k < n ? y[sa[i] + k] : -1)) ? p - 1 : p++;
        if (p >= n)
            break;
        m = p;
    }
    return sa;
}

vector<int> build_lcp(const vector<int> &s, int n, const vector<int> &sa)
{
    vector<int> rank(n), lcp(n, 0);
    for (int i = 0; i < n; i++)
        rank[sa[i]] = i;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (rank[i] == n - 1)
        {
            k = 0;
            continue;
        }
        if (k)
            k--;
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            k++;
        lcp[rank[i]] = k;
    }
    return lcp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> s(n);
    int max_v = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        max_v = max(max_v, s[i]);
    }

    if (n == 0)
        return 0;

    vector<int> sa = build_sa(s, n, max_v);
    vector<int> lcp = build_lcp(s, n, sa);

    ll total_sum = (ll)n * (n + 1) / 2;

    int m = n - 1;
    vector<int> L(m), R(m);
    stack<int> st;

    for (int i = 0; i < m; i++)
    {
        while (!st.empty() && lcp[st.top()] >= lcp[i])
            st.pop();
        L[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    while (!st.empty())
        st.pop();

    for (int i = m - 1; i >= 0; i--)
    {
        while (!st.empty() && lcp[st.top()] > lcp[i])
            st.pop();
        R[i] = st.empty() ? m : st.top();
        st.push(i);
    }

    ll lcp_pairs_sum = 0;
    for (int i = 0; i < m; i++)
    {
        lcp_pairs_sum += (ll)lcp[i] * (i - L[i]) * (R[i] - i);
    }

    total_sum += 2 * lcp_pairs_sum;

    ll denominator = (ll) n * n;
    ll common = gcd(total_sum, denominator);

    cout << total_sum / common << "/" << denominator / common << endl;
}

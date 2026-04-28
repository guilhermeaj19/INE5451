#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXK = 20000001;
int min_prime[MAXK];
int distinct_primes[MAXK];

void precompute()
{
    for (int i = 2; i < MAXK; i++)
    {
        if (distinct_primes[i] == 0)
        {
            for (int j = i; j < MAXK; j += i)
            {
                distinct_primes[j]++;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int t;
    cin >> t;
    while (t--)
    {
        int c, d, x;
        cin >> c >> d >> x;

        ll total_pairs = 0;

        for (int g = 1; g * g <= x; g++)
        {
            if (x % g == 0)
            {

                int val1 = x / g + d;
                if (val1 % c == 0)
                {
                    int k = val1 / c;
                    total_pairs += (1LL << distinct_primes[k]);
                }

                if (g * g != x)
                {
                    int g2 = x / g;
                    int val2 = x / g2 + d;
                    if (val2 % c == 0)
                    {
                        int k = val2 / c;
                        total_pairs += (1LL << distinct_primes[k]);
                    }
                }
            }
        }
        cout << total_pairs << "\n";
    }

    return 0;
}
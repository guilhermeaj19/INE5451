#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef __int128_t int128;

void print128(int128 x)
{
    if (x == 0)
    {
        cout << "0";
        return;
    }
    string s = "";
    while (x > 0)
    {
        s += (char)('0' + (x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main()
{

    ll n_ll, k_ll;
    cin >> n_ll >> k_ll;

    int128 n = n_ll;
    int128 k = k_ll;

    int128 result = n * k;

    int128 limit = min((int128)n_ll, (int128)k_ll);

    for (int128 l = 1, r; l <= limit; l = r + 1)
    {
        int128 quotient = k_ll / l;

        r = min((int128)limit, (int128)(k_ll / quotient));

        int128 range_count = (r - l + 1);
        int128 range_sum = (int128)(l + r) * range_count / 2;

        result -= range_sum * quotient;
    }

    if (result == 0)
        cout << 0 << endl;
    else
    {
        print128(result);
        cout << endl;
    }

    return 0;
}
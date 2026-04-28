#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef __int128_t int128;

string int128ToString(int128 n)
{
    if (n == 0)
        return "0";
    string s = "";
    while (n > 0)
    {
        char c = (char)('0' + (int)(n % 10));
        s = c + s;
        n /= 10;
    }
    return s;
}

int128 powerOfTwoMod(int128 exp, int128 mod)
{
    int128 res = 1;
    int128 base = 2 % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (int128)res * base % mod;
        base = (int128)base * base % mod;
        exp /= 2;
    }
    return res;
}

int main()
{
    string results[21];
    int128 current_K = 1;
    int128 current_period = 4;
    int128 p10 = 10;

    results[1] = "1";

    for (int r = 2; r <= 20; ++r)
    {
        p10 *= 10;
        while (true)
        {
            int128 val = powerOfTwoMod(current_K, p10);
            int128 digit_val = (val / (p10 / 10)) % 10;

            if (digit_val == 1 || digit_val == 2)
            {
                results[r] = int128ToString(current_K);
                break;
            }
            current_K += current_period;
        }

        current_period *= 5;
    }

    int N, R;
    cin >> N;
    for (int i = 1; i <= N; ++i)
    {   
        cin >> R;
        cout << i << " " << R << " " << results[R] << endl;
    }

    return 0;
}
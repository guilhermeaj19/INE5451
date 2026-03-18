#include <bits/stdc++.h>

using namespace std;

long long get_operator(string s, long long mod)
{
    long long sum = 0;

    for (char c : s)
    {
        long long digit = c - '0';
        sum = (sum * 10 + digit) % mod;
    }

    return sum;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s1, s2;
    char operation;
    long long MOD = 1000000007;

    cin >> s1 >> operation >> s2;
    long long op1 = get_operator(s1, MOD);
    
    long long op2 = operation == '^' ? get_operator(s2, MOD - 1) : get_operator(s2, MOD);
    

    if (operation == '+')
    {
        cout << (op1 + op2) % MOD << endl;
    }
    else if (operation == '*')
    {
        cout << (op1 * op2) % MOD << endl;
    }
    else if (operation == '-')
    {
        cout << (op1 - op2 + MOD) % MOD << endl;
    }
    else if (operation == '^')
    {
        long long result = 1;
        long long base = op1 % MOD;
        long long exp = op2;

        // Exponenciação binária
        while (exp > 0)
        {
            if (exp % 2)
            {
                result = (result * base) % MOD;
            }
            base = (base * base) % MOD;
            exp /= 2;
        }

        cout << result << endl;
    }

    return 0;
}
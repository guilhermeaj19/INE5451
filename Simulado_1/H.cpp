#include <bits/stdc++.h>

using namespace std;

long long MOD = 1000000007;

// Exponenciação binária
long long power(long long base, long long exp)
{
    long long result = 1;
    base = base % MOD;

    if (base == 0)
        return 0;

    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    long long n;
    cin >> n;
    long long fact = 1;
    long long desarranjo = 0;

    // Desarranjo ajustado para cálculo em recorrência
    for (long long i = 2; i <= n; i++)
    {
        fact = (fact * i) % MOD;

        desarranjo = (desarranjo * i) % MOD;

        if (i % 2 == 0)
        {
            desarranjo = (desarranjo + 1) % MOD;
        }
        else
        {
            desarranjo = (desarranjo - 1 + MOD) % MOD;
        }
    }

    long long a = (fact - desarranjo + MOD) % MOD; // Casos que uma pessoa sorteia ela mesma (n! - desarranjo)

    long long b = fact; // Total de casos possíveis (n!)

    // Teorema de Fermat 
    // b^(M-1) <congruente> 1      mod M (multiplica-se ambos os lados por b^(-1))
    // b^(M-2) <congruente> b^(-1) mod M
    long long inverso_b = power(b, MOD - 2);

    cout << (a * inverso_b) % MOD << '\n';

    return 0;
}
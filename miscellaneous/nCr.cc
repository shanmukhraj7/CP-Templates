# include <bits/stdc++.h>
using namespace std;

const int64_t mod = 1e9 + 7;
const int64_t N = 2e5;

int64_t fact[N + 1], inv_fact[N + 1];

// used to calculate a ^ b
int64_t binexpo(int64_t a, int64_t b) {
    int64_t res = 1;
    a %= mod;
    while(b) {
        if(b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// fermat's little theorem and works only if mod is prime !!!
int64_t inv_mod(int64_t a) {
    return binexpo(a, mod - 2);
}

void precompute() {
    fact[0] = 1;
    for(int64_t i = 1; i <= N; i++)
        fact[i] = (fact[i - 1] * i) % mod;
    inv_fact[N] =  inv_mod(fact[N]);
    for(int64_t i = N; i >= 1; i--)
        inv_fact[i - 1] = (inv_fact[i] * i) % mod;
}

int64_t nCr(int64_t n, int64_t r) {
    if(r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] % mod * inv_fact[n - r] % mod;
}
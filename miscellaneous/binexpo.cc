# include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

// used to calculate a ^ b in log N time
int binexpo(int a, int b) {
    int res = 1;
    a %= mod;
    while(b) {
        if(b & 1) res *= a % mod;
        a *= a % mod;
        b >>= 1;
    }
    return res;
}

// fermat's little theorem and works only if mod is prime !!!
int inv_mod(int a) {
    return binexpo(a, mod - 2);
}
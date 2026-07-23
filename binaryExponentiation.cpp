# include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int binexpo(int a, int b){
    int ans = 1;
    a %= mod;
    while(b){
        if(b & 1) ans *= a % mod;
        a *= a % mod;
        b >>= 1;
    }
    return ans;
}

int modinv(int a){
    return binexpo(a, mod - 2);
}
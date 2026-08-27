# include <bits/stdc++.h>
using namespace std;

int64_t gcd(int64_t a, int64_t b){
    while(b){
        a %= b;
        swap(a, b);
    }
    return a;
}

int64_t lcm(int64_t a, int64_t b){
    return (a / gcd(a, b)) * b;
}

struct CRT {
    vector<int64_t> rem, mod;

    CRT() {}

    CRT(vector<int64_t> _rem, vector<int64_t> _mod) {
        rem = _rem;
        mod = _mod;
    }

    int64_t calculate() {
        int64_t ans = rem[0], val = mod[0];
        ans = ((ans % val) + val) % val;

        for(int i = 1; i < rem.size(); ++i) {
            int64_t r = ((rem[i] % mod[i]) + mod[i]) % mod[i];
            int64_t m = mod[i];
            int64_t g = gcd(val, m);

            if((r - ans) % g != 0) {
                return -1;
            }

            while(ans % m != r) {
                ans += val;
            }
            val = val / g * m;
        }
        
        return ans;
    }

};
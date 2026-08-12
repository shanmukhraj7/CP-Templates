# include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Fenwick {
    int n;
    vector<T> a;

    Fenwick(int _n = 0) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        a.assign(n, T{});
    } 

    void add(int x, const T &v) {
        for(int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }

    T sum(int x) const {
        T ans{};
        for(int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }

    T range_sum(int l, int r) const {
        return sum(r) - sum(l);
    }

    int select(const T &k) const {
        int x = 0;
        T cur{};
        
        for(int i = 1 << __lg(n); i; i /= 2) {
            if(x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur += a[x - 1];
            }
        }
        return x;
    }
};
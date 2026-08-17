# include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> factors(T n) {
    vector<T> res;
    for (T i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            res.push_back(i);
            if (i * i != n) {
                res.push_back(n / i);
            }
        }
    }
    return res;
}
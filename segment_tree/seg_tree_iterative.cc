# include <bits/stdc++.h>
using namespace std;


struct Sum {
    int operator()(int a, int b) const {
        return a + b;
    }

    static int identity() {
        return 0;
    }
};

template<typename T, class Op> 
struct Segment {
    int n;
    vector<T> seg;
    Op op;
    
    Segment(int _n = 0, Op _op = Op()) {
        init(_n);
        op = _op;
    }

    void init(int _n) {
        n = _n;
        seg.assign(2 * n, Op::identity());
    }

    void build(const vector<T>& a) {
        for(int i = 0; i < n; ++i){
            seg[i + n] = a[i];
        }

        for(int i = n - 1; i >= 1; --i) {
            seg[i] = op(seg[2 * i], seg[2 * i + 1]);
        }
    }

    void update(int i, const T& v) {
        i += n;
        seg[i] = v;

        for(i /= 2; i >= 1; i /= 2) {
            seg[i] = op(seg[2 * i], seg[2 * i + 1]);
        }
    }

    T query(int l, int r) const {
        T left = Op::identity();
        T right = Op::identity();

        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) {
                left = op(left, seg[l]);
                ++l;
            }
            if(r & 1) {
                --r;
                right = op(seg[r], right);
            }
        }

        return op(left, right);
    }
};
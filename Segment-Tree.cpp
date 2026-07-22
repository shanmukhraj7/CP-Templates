# include <bits/stdc++.h>
using namespace std;

# define int long long
# define vi vector<int>

class SGT{
public:
    vi seg, lz;
    SGT(int n){
        seg.resize(4 * n + 5);
        // lz.resize(4 * n + 5, 0);
    }

    // void push(int idx, int low, int high){
    //     if(lz[idx] == 0) return;
    //     seg[idx] += lz[idx];
    //     if(low != high){
    //         lz[idx << 1] += lz[idx];
    //         lz[idx << 1 | 1] += lz[idx];
    //     }
    //     lz[idx] = 0;
    // }

    void build(int idx, int low, int high, vi& a){
        if(low == high){
            seg[idx] = a[low];
            return;
        }
        int mid = low + ((high - low) >> 1);
        build(idx << 1, low, mid, a);
        build(idx << 1 | 1, mid + 1, high, a);
        seg[idx] = max(seg[idx << 1], seg[idx << 1 | 1]);
    }

    void update(int idx, int low, int high, int ui, int uv){
        // push(idx, low, high);
        if(low == high){
            seg[idx] = uv;
            return;
        }
        int mid = low + ((high - low) >> 1);
        if(ui <= mid){
            update(idx << 1, low, mid, ui, uv);
        }
        else{
            update(idx << 1 | 1, mid + 1, high, ui, uv);
        }
        seg[idx] =max(seg[idx << 1], seg[idx << 1 | 1]);
    }

    int query(int idx, int low, int high, int ql, int qr){
        // push(idx, low, high);
        if(qr < low || high < ql) return LLONG_MIN;
        if(ql <= low && high <= qr) return seg[idx];
        int mid = low + ((high - low) >> 1);
        int left = query(idx << 1, low, mid, ql, qr);
        int right = query(idx << 1 | 1, mid + 1, high, ql, qr);
        return max(left, right);
    }

    // void lzyupdate(int idx, int low, int high, int ql, int qr, int val){
    //     push(idx, low, high);
    //     if(high < ql || qr < low) return;
    //     if(ql <= low && high <= qr){
    //         lz[idx] += val;
    //         push(idx, low, high);
    //         return;
    //     }
    //     int mid = low + ((high - low) >> 1);
    //     lzyupdate(idx << 1, low, mid, ql, qr, val);
    //     lzyupdate(idx << 1 | 1, mid + 1, high, ql, qr, val);
    //     seg[idx] = max(seg[idx << 1], seg[idx << 1 | 1]);
    // }
};
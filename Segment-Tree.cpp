# include <bits/stdc++.h>
using namespace std;

# define int long long
# define vi vector<int>

class SGT{
public:
    vi seg;
    SGT(int n){
        seg.resize(4 * n + 5);
    }

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
        if(qr < low || high < ql) return INT_MAX;
        if(ql <= low && high <= qr) return seg[idx];
        int mid = low + ((high - low) >> 1);
        int left = query(idx << 1, low, mid, ql, qr);
        int right = query(idx << 1 | 1, mid + 1, high, ql, qr);
        return max(left, right);
    }
};
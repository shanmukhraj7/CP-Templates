# include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

struct SGT {

    vector<int> seg, lz;

    SGT(int n) {
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

    void build(int idx, int low, int high, vector<int> &a) {
        if (low == high) {
            seg[idx] = a[low];
            return;
        }

        int mid = low + ((high - low) >> 1);

        build(idx << 1, low, mid, a);
        build(idx << 1 | 1, mid + 1, high, a);

        seg[idx] = max(seg[idx << 1], seg[idx << 1 | 1]);
    }

    void update(int idx, int low, int high, int ui, int uv) {
        // push(idx, low, high);

        if (low == high) {
            seg[idx] = uv;
            return;
        }

        int mid = low + ((high - low) >> 1);

        if (ui <= mid)
            update(idx << 1, low, mid, ui, uv);
        else
            update(idx << 1 | 1, mid + 1, high, ui, uv);

        seg[idx] = max(seg[idx << 1], seg[idx << 1 | 1]);
    }

    int query(int idx, int low, int high, int ql, int qr) {
        // push(idx, low, high);

        if (qr < low || high < ql)
            return LLONG_MIN;

        if (ql <= low && high <= qr)
            return seg[idx];

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

struct HLD {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> A, parent, head, position, heavy, depth, flatten, size;
    
    SGT seg;

    HLD(int N) : n(N), timer(0), seg(N) {
        adj.assign(n, {});
        parent.assign(n, -1);
        depth.assign(n, 0);
        size.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        position.assign(n, 0);
        A.assign(n, 0);
        flatten.assign(n, 0);
    }

    void add_edge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);        
    }

    int dfs(int v, int p = -1) {
        parent[v] = p;
        size[v] = 1;
        int maxi = 0;
        for(int u : adj[v]) {
            if(u == p)
                continue;
            
            depth[u] = depth[v] + 1;
            dfs(u, v);
            size[v] += size[u];
            if(size[u] > maxi) {
                maxi = size[u];
                heavy[v] = u;
            }
        }
        return size[v];
    }

    void decompose(int v, int h) {
        head[v] = h;
        position[v] = timer;
        flatten[timer] = A[v];
        timer++;
        
        if(heavy[v] != -1) {
            decompose(heavy[v], h);
        }

        for(auto u : adj[v]) {
            if(u == parent[v] || u == heavy[v])
                continue;
            
            decompose(u, u);
        }
    }

    void build(int root = 0) {
        dfs(root);
        decompose(root, root);
        seg.build(1, 0, n - 1, flatten);
    }

    void update(int update_node, int update_value) {
        seg.update(1, 0, n - 1, position[update_node], update_value);
        A[update_node] = update_value;
    }

    int query(int u, int v) {
        // finding the maximum
        int ans = INT_MIN;

        while(head[u] != head[v]) {
            if(depth[head[u]] < depth[head[v]])
                swap(u, v);
            
            ans = max(ans, seg.query(1, 0, n - 1, position[head[u]], position[u]));
            u = parent[head[u]];
        }

        if(depth[u] > depth[v])
            swap(u, v);

        ans = max(ans, seg.query(1, 0, n - 1, position[u], position[v]));

        return ans;
    }
};
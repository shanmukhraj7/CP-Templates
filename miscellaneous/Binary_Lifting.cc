# include <bits/stdc++.h>
using namespace std;

struct BinaryLifting {

    int N;

    // change this to 63 if taking int64_t
    static const int LOG = 31;

    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> depth;

    BinaryLifting(int n) {
        N = n;
        adj.assign(N + 1, {});
        up.assign(N + 1, vector<int>(LOG, -1));
        depth.assign(N + 1, 0);
    }

    void add_edge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    void dfs(int u, int p) {
        up[u][0] = p;

        for(int v : adj[u]) {
            if(v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    void build(int root = 1) {
        depth[root] = 0;
        dfs(root, -1);

        for(int j = 1; j < LOG; j++) {
            for(int i = 1; i <= N; i++) {
                if(up[i][j - 1] != -1)
                    up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }

    int kth_ancestor(int u, int k) {
        for(int j = 0; j < LOG; j++) {
            if(k & (1 << j))
                u = up[u][j];

            if(u == -1)
                break;
        }

        return u;
    }

    int lca(int a, int b) {
        if(depth[a] < depth[b])
            swap(a, b);

        int diff = depth[a] - depth[b];
        for(int j = LOG - 1; j >= 0; j--) {
            if(diff & (1 << j))
                a = up[a][j];
        }

        if(a == b)
            return a;

        for(int j = LOG - 1; j >= 0; j--) {
            if(up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }

        return up[a][0];
    }

    int dist(int u, int v) {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }
};
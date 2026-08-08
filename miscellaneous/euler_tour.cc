# include <bits/stdc++.h>
using namespace std;


struct Euler_Tour { 
    int n, timer = 0;
    vector<int> tin, tout, euler_path, parent;
    vector<vector<int>> adj;

    Euler_Tour(int _n) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        tin.resize(n + 1);
        tout.resize(n + 1);
        adj.resize(n + 1);
        euler_path.resize(n);
        parent.resize(n + 1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void tour_dfs(int u, int p = 0) {
        parent[u] = p;
        tin[u] = timer;
        euler_path[timer++] = u;
        for(auto& v : adj[u]) {
            if(v == p)
                continue;
            tour_dfs(v, u);
        }
        tout[u] = timer - 1;
    }

    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }
};

int32_t main() {
    int N, M;
    cin >> N >> M;
    
    Euler_Tour et(N);
    
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        et.add_edge(u, v);
    }

    et.tour_dfs(1);

    for(int i = 0; i <= N; i++) {
        cout << "Node : " << i << '\t' << " In Time : "  << et.tin[i] << '\t' << "Out Time : " << et.tout[i] << '\n';
    }
}
# include <bits/stdc++.h>
using namespace std;

const int INF = int(1e9) + 5;

struct BFS {

    struct edge {
        int node = -1, weight = -1;

        edge() {}

        edge(int _node, int _weight) : node(_node), weight(_weight) {}
    };

    int n;
    vector<vector<edge>> adj;
    vector<int> par;
    vector<int> dist;

    BFS(int _n = 0) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        adj.assign(n, {});
    }

    void add_directional_edge(int a, int b, int weight) {
        assert(0 <= weight && weight <= 1);
        adj[a].emplace_back(b, weight);
    }

    void add_bidirectional_edge(int a, int b, int weight) {
        add_directional_edge(a, b, weight);
        add_directional_edge(b, a, weight);
    }

    void bfs_check(queue<int>& q, queue<int>& next_q, int node, int from, int new_dist, int add) {
        assert(add == 0 || add == 1);
        
        if(new_dist < dist[node]) {
            dist[node] = new_dist;
            par[node] = from;
            (add == 0 ? q : next_q).push(node);
        }
    }

    void bfs(const vector<int>& source) {
        if(n == 0)
            return;
        
        // need two queues for 0-1 BFS.
        queue<int> q, next_q;
        dist.assign(n, INF);
        par.assign(n, -1);

        for(int src : source)
            bfs_check(q, next_q, src, -1, 0, 0);
        
        int level = 0;

        while(!q.empty() || !next_q.empty()) {
            while(!q.empty()) {
                int top = q.front(); q.pop();

                if(level > dist[top])
                    continue;
                
                for(edge& e : adj[top])
                    bfs_check(q, next_q, e.node, top, dist[top] + e.weight, e.weight);
            }
            q.swap(next_q);
            level++;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    BFS bfs(N);

    for(int i = 0; i < M; i++) {
        int a, b, weight;
        cin >> a >> b >> weight;
        a--, b--;
        bfs.add_bidirectional_edge(a, b, weight);
    }

    bfs.bfs({0});

    int total = 0;
    for(int i = 0; i < N; i++){
        total += bfs.dist[i];
    }
    cout << total << '\n';
}
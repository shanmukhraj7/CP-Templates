# include <bits/stdc++.h>
using namespace std;

# define vi vector<int>

class DSU{
public:
    vi par, sz;
    DSU(int n){
        par.resize(n);
        sz.resize(n, 1);
        for(int i = 0; i < n; i++) par[i] = i;
    }

    int findpar(int u){
        return u == par[u] ? u : par[u] = findpar(par[u]);
    }

    void merge(int u, int v){
        int pu = findpar(u), pv = findpar(v);
        if(pu == pv) return;
        if(sz[pu] < sz[pv]) swap(pu, pv);
        par[pv] = pu;
        sz[pu] += pv;
    }
};
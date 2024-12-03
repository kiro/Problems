#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int N, S, Q, E;

vector<pair<int, int>> edges;
vector<vector<pair<int, int>>> g;
vector<bool> shop;

vector<vector<int>> parent;
vector<vector<long long>> cost;
vector<vector<long long>> closest; 

const long long INF = 1E15L; 

long long hang(int p, int u, int c) {
    parent[u].push_back(p);
    cost[u].push_back(c);
   
    closest[u].push_back(shop[u] ? 0 : INF);
    for (auto e : g[u]) {
        auto [v, c] = e;
        if (v != p) {
            closest[u][0] = min(closest[u][0], (long long)c + hang(u, v, c));
        }
    }
    return closest[u][0];
}

void binaryLift() {
    for (int i = 1; (1 << i) <= N*2; i++) {
        for (int v = 1; v <= N; v++) {
            int u = parent[v][i-1];
            parent[v].push_back(parent[u][i-1]);
            cost[v].push_back(cost[v][i-1] + cost[u][i-1]);
            closest[v].push_back( min(closest[v][i-1], cost[v][i-1] + closest[u][i-1] ));
        }
    }
}

int depth(int u) {
    int res = 0;
    for (int i = parent[u].size() - 1; i >= 0; i--) {
        if (parent[u][i] != 0) {
            res += (1 << i);
            u = parent[u][i];
        }    
    }
    return res;
}

int moveup(int u, int k) {
    for (int i = parent[E].size() - 1; i >= 0; i--) {
        if ( (1 << i) <= k ) {
            u = parent[u][i];
            k -= 1 << i;
        }
    }
    return u;
}

int lca(int u, int v) {
    int du = depth(u);
    int dv = depth(v);
    u = moveup(u, max(du - dv, 0));
    v = moveup(v, max(dv - du, 0));

    for (int i = parent[E].size() - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    if (u == v) {
        return u;
    }
    return parent[u][0];
}

string closestShop(int u, int k) {
    int costToU = 0;
    long long res = INF;
    for (int i = parent[E].size() - 1; i >= 0; i--) {
        if ( (1 << (i - 1)) <= k ) {
            res = min(res, costToU + closest[u][i]);
            k -= (1 << i);
            costToU += cost[u][i];
            u = parent[u][i];
        }
    }

    return res == INF ? "oo" : to_string(res);
}

int main() {
    cin >> N >> S >> Q >> E;

    shop.resize(N + 1);
    g.resize(N + 1);
    parent.resize(N + 1);
    cost.resize(N + 1);
    closest.resize(N + 1);
    parent[0].push_back(0);
    cost[0].push_back(0);
    closest[0].push_back(INF);
   
    for (int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        edges.push_back({u, v});
    }

    for (int i = 0; i < S; i++) {
        int v;
        cin >> v;
        shop[v] = true;
    }

    hang(0, E, 0);
    binaryLift();

    for (int q = 0; q < Q; q++) {
        int i, r;
        cin >> i >> r;

        auto [u, v] = edges[i - 1]; 
        int du = depth(u);
        int dv = depth(v);
        int dr = depth(r);
 
        if (du < dv) {
            swap(u, v);
            swap(du, dv);
        }

        int ru = lca(r, u);
        if (ru != u) {
            cout << "escaped" << endl;
        } else {
            cout << closestShop(r, dr - du) << endl;
        }
    }

    return 0;
}
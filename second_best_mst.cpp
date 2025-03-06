#pragma optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;

struct edge {
    int u, v, cost;
};

bool operator<(const edge& lhs, const edge& rhs) {
    return lhs.cost < rhs.cost;
}

int n, l; // n is number of nodes, l is log_2 n
vector<vector<pii>> mst_edges; // adj list, stores {dest, cost}

int timer;
vi tin, tout;
vi depth;
vvi up;
vvi dp; // max edge from here to parent 2^i above 

void dfs(int v, int p, int d) {
    tin[v] = ++timer;
    depth[v] = depth[p] + 1;
    up[v][0] = p;
    dp[v][0] = d;

    for (pii edge : mst_edges[v]) {
        int u = edge.first;
        int cost = edge.second;
        if (u != p) {
            dfs(u, v, cost);
        }
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

// v needs to be a parent of u
int max_along_path(int u, int v) {
    int ans = 0;
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    for (int i = l - 1; i >= 0; i--) {
        if (depth[u] - depth[v] >= (1 << i)) {
            ans = max(ans, dp[u][i]);
            u = up[u][i];
        }
    }
    return ans;
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dp.assign(n, vector<int>(l + 1));

    depth.resize(n);
    depth[root] = 0;

    dfs(root, root, 0);

    for (int i = 1; i <= l - 1; i++) {
        for (int j = 1; j < n; j++) {
            int v = up[j][i - 1];
            up[j][i] = up[v][i - 1];
            dp[j][i] = max(dp[j][i - 1], dp[v][i - 1]);
        }
    }
}

struct DSU {
    vi parent, size;

    void init_dsu(int n) {
        parent = vi(n);
        size = vi(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a == b)
            return;
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    // read input
    int m;
    cin >> n >> m;
    n++; // account for 1 indexing

    vector<edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(edge{u, v, w});
    }

    // build mst
    DSU dsu;
    dsu.init_dsu(n + 1);
    
    sort(edges.begin(), edges.end());
    mst_edges.resize(n + 1);
    vector<edge> remaining_edges;
    ll mst_weight = 0;
    for (int i = 0; i < edges.size(); i++) {
        edge e = edges[i];
        if (dsu.find_set(e.u) != dsu.find_set(e.v)) {
            dsu.union_sets(e.u, e.v);
            mst_weight += e.cost;
            mst_edges[e.u].push_back(make_pair(e.v, e.cost));
            mst_edges[e.v].push_back(make_pair(e.u, e.cost));
        } else {
            remaining_edges.push_back(e);
        }
    }

    // do preprocessing for lca
    preprocess(1);

    // get answer
    ll ans = LLONG_MAX;
    for (edge e : remaining_edges) {
        int parent = lca(e.u, e.v);
        int first = max_along_path(e.u, parent);
        int second = max_along_path(e.v, parent);
        ans = min(ans, mst_weight - max(first, second) + e.cost);
    }

    cout << ans << endl;
    
}

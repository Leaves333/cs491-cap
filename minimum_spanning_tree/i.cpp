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

struct edge {
    int a, b, weight;
};

bool operator<(const edge& first, const edge& second) {
    return first.weight < second.weight;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = edge{u, v, w};
    }

    sort(edges.begin(), edges.end());
    DSU dsu;
    dsu.init_dsu(n + 1);

    ll total_weight = 0;
    vector<pii> mst_edges;
    for (auto e : edges) {
        if (dsu.find_set(e.a) == dsu.find_set(e.b))
            continue;
        total_weight += e.weight;
        mst_edges.push_back(make_pair(e.a, e.b));
        dsu.union_sets(e.a, e.b);
    }

    cout << total_weight << endl;
    for (auto p : mst_edges) {
        cout << p.first << " " << p.second << endl;
    }
}

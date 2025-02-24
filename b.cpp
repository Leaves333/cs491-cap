#include <climits>
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

    ll n, m, k, t;
    cin >> n >> m >> k >> t;
    vi buildings(k);
    for (int i = 0; i < k; i++) {
        cin >> buildings[i];
    }

    ll d[n+1][n+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            d[i][j] = LLONG_MAX;
        }
    }
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        d[u][v] = w;
        d[v][u] = w;
    }

    // do floyd warshall
    for (int k = 0; k <= n; k++) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (d[i][k] < LLONG_MAX && d[k][j] < LLONG_MAX)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    // store valid edges
    vector<pii> edges;
    for (int i : buildings) {
        for (int j : buildings) {
            if (d[i][j] <= t)
                edges.push_back(make_pair(i, j));
        }
    }

    DSU dsu;
    dsu.init_dsu(n + 1);
    for (pii p : edges) {
        dsu.union_sets(p.first, p.second);
    }

    set<int> parents;
    for (int b : buildings) {
        parents.insert(dsu.find_set(b));
    }

    if (parents.size() == 1) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

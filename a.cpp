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
    vi parent = vi(1000000);
    vi size = vi(1000000);

    void make_set(int v) {
        parent[v] = v;
        size[v] = 1;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    DSU dsu;
    for (int i = 0; i < n; i++) {
        dsu.make_set(i);
    }

    while (m--) {
        string op;
        cin >> op;
        if (op == "Union") {
            int u, v;
            cin >> u >> v;
            dsu.union_sets(--u, --v);
        } else {
            int k;
            cin >> k;
            int ans = dsu.size[dsu.find_set(--k)];
            cout << ans << endl;
        }
    }
}

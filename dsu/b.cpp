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
    vi parent = vi(100000);
    vi size = vi(100000);

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

    int n, m, k;
    cin >> n >> m >> k;
    
    set<pii> edges;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        edges.insert(make_pair(x, y));
    }

    vector<pii> earthquakes;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        earthquakes.push_back(make_pair(x, y));
        edges.erase(make_pair(x, y));
    }

    DSU dsu;
    for (int i = 0; i < n; i++) {
        dsu.make_set(i);
    }

    set<int> components;
    for (auto e : edges) {
        dsu.union_sets(e.first, e.second);
    }

    for (int i = 0; i < n; i++) {
        components.insert(dsu.find_set(i));
    }

    vector<pii> ans;
    reverse(earthquakes.begin(), earthquakes.end());
    for (auto e : earthquakes) {
        ans.push_back(make_pair(dsu.size[dsu.find_set(0)], components.size()));
        components.erase(dsu.find_set(e.first));
        components.erase(dsu.find_set(e.second));
        dsu.union_sets(e.first, e.second);
        components.insert(dsu.find_set(e.first));
    }

    reverse(ans.begin(), ans.end());
    for (auto x : ans) {
        cout << x.first << " " << x.second << endl;
    }

}

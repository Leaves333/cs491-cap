#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> parent;
vector<int> level;
ll const INF = 1e9;

vector<vector<ll>> floyd_warshall(vector<vector<ll>> &arr, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (arr[i][j] > (arr[i][k] + arr[k][j])) {
                    arr[i][j] = arr[i][k] + arr[k][j];
                }
            }
        }
    }
    return arr;
}

void make_set(int v) {
    parent[v] = v;
    level[v] = 0;
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
        if (level[a] < level[b])
            swap(a, b);
        parent[b] = a;
        if (level[a] == level[b])
            level[a]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, t;
    cin >> n >> m >> k >> t;
    parent.resize(n);
    level.resize(n);

    vector<int> buildings(k); // buildings that we have to reach
    for (int i = 0; i < k; i++) {
        int temp;
        cin >> temp;
        buildings[i] = temp;
    }
    vector<vector<ll>> adjlist(n, vector<ll>(n, INF));
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        adjlist[u - 1][v - 1] = w;
        adjlist[v - 1][u - 1] = w;
    }
    for (int i = 0; i < n; i++) {
        adjlist[i][i] = 0; // set diagonal to 0
    }

    floyd_warshall(adjlist, n);

    vector<vector<ll>> edges;
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            int u = buildings[i] - 1;
            int v = buildings[j] - 1;
            ll w = adjlist[u][v];
            if (w < INF) {
                edges.push_back({w, u, v});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        make_set(i);
    }

    sort(edges.begin(), edges.end());

    vector<pair<int, int>> result;
    ll mst_cost = 0;
    for (vector<ll> edge : edges) {
        if (find_set(edge[1]) != find_set(edge[2])) {
            mst_cost += edge[0];
            result.push_back(make_pair(edge[1], edge[2]));
            union_sets(edge[1], edge[2]);
        }
    }
    if (mst_cost < t) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}

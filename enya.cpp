#pragma GCC optimize("O3,unroll-loops")
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
const int INF = 1000000000;
// adj[vertex] is the list of edges going from this vertex
// // list of pair<int, int> which represents vertex, weight
vector<vector<pair<int, int>>> adj;

void dijkstra(int s, vector<int> &dist, vector<int> &p) {
    int n = adj.size();
    dist.assign(n, INF);
    p.assign(n, -1);

    dist[s] = 0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        q.pop();

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (dist[v] + len < dist[to]) {
                dist[to] = dist[v] + len;
                p[to] = v;
                q.push({dist[to], to});

            }
        }
    }
}


    // Dijkstra!
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n);
    vector<int> dist;
    vector<int> p;
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        u--, v--;

        adj[u].emplace_back(v, weight);
    }
    dijkstra(0, dist, p);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            cout << -1 << " ";
        } else {
            cout << dist[i] << " ";

        }
    }
}

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

map<int, vector<pii>> edges;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back(make_pair(v, w));
    }

    map<int, ll> dist;
    dist[1] = 0;

    priority_queue<pll, vector<pll>, std::greater<pll>> pq;
    pq.push(make_pair(0, 1));

    while (!pq.empty()) {
        ll location = pq.top().second;
        ll cur_dist = pq.top().first;
        pq.pop();
        for (pii edge : edges[location]) {
            ll new_dist = cur_dist + edge.second;
            if (!dist.count(edge.first) || new_dist < dist[edge.first]) {
                dist[edge.first] = new_dist;
                pq.push(make_pair(new_dist, edge.first));
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!dist.count(i)) {
            cout << "-1" << " ";
        } else {
            cout << dist[i] << " ";
        }
    }
    cout << endl;
}

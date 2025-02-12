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
    int dest, weight;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k, t;
    cin >> n >> m >> k >> t;

    set<int> trains;
    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        trains.insert(x);
    }

    map<int, vector<edge>> edges;
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        edges[x].push_back(edge{y, w});
        edges[y].push_back(edge{x, w});
    }

    map<int, ll> dist;
    dist[1] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push(make_pair(0, 1));

    while (!pq.empty()) {
        ll cur_loc = pq.top().second;
        ll cur_dist = pq.top().first;
        pq.pop();

        for (edge e : edges[cur_loc]) {
            ll new_dist = cur_dist + e.weight;
            if (!dist.count(e.dest) || new_dist < dist[e.dest]) {
                dist[e.dest] = new_dist;
                pq.push(make_pair(new_dist, e.dest));
            }
        }

        if (trains.count(cur_loc)) {
            ll new_dist = cur_dist + t;
            for (int dest : trains) {
                if (!dist.count(dest) || new_dist < dist[dest]) {
                    dist[dest] = new_dist;
                    pq.push(make_pair(new_dist, dest));
                }
            }
        }
    }

    if (!dist.count(n)) {
        cout << -1 << endl;
    } else {
        cout << dist[n] << endl;
    }
}

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

    // get input
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

    // djikstra from start
    vll dist_from_start(n+1, LLONG_MAX);
    dist_from_start[1] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push(make_pair(0, 1));

    while (!pq.empty()) {
        ll cur_loc = pq.top().second;
        ll cur_dist = pq.top().first;
        pq.pop();

        for (edge e : edges[cur_loc]) {
            ll new_dist = cur_dist + e.weight;
            if (new_dist < dist_from_start[e.dest]) {
                dist_from_start[e.dest] = new_dist;
                pq.push(make_pair(new_dist, e.dest));
            }
        }
    }

    // djikstra from kend
    vll dist_from_end(n+1, LLONG_MAX);
    dist_from_end[n] = 0;
    pq.push(make_pair(0, n));

    while (!pq.empty()) {
        ll cur_loc = pq.top().second;
        ll cur_dist = pq.top().first;
        pq.pop();

        for (edge e : edges[cur_loc]) {
            ll new_dist = cur_dist + e.weight;
            if (new_dist < dist_from_end[e.dest]) {
                dist_from_end[e.dest] = new_dist;
                pq.push(make_pair(new_dist, e.dest));
            }
        }
    }

    // calculate final answer
    ll closest_from_start = LLONG_MAX;
    ll closest_from_end = LLONG_MAX;
    for (int t : trains) {
        closest_from_start = min(closest_from_start, dist_from_start[t]);
        closest_from_end = min(closest_from_end, dist_from_end[t]);
    }

    ll dist_with_train = LLONG_MAX;
    ll dist_no_train = dist_from_start[n];

    if (closest_from_start != LLONG_MAX && closest_from_end != LLONG_MAX) {
        dist_with_train = closest_from_start + closest_from_end + t;
    }

    if (min(dist_with_train, dist_no_train) == LLONG_MAX) {
        cout << -1 << endl;
    } else {
        cout << min(dist_with_train, dist_no_train) << endl;
    }

}

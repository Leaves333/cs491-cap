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
    int dest, cost;
};

// mask: bitmask of visited cities
// cur: current city we're at
// n: total number of cities
// edges: adjacency matrix of distances
// dp: memoization of states
ll tsp(int mask, int cur, int n, const vvll &edges, vvll &dp) {

    // base case: all cities visited
    if (mask == (1 << n) - 1)
        return 0;

    // this case is in our dp
    if (dp[cur][mask] != -1)
        return dp[cur][mask];

    ll ans = INT_MAX;

    // try visiting every unvisited city
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) == 0) {
            if (edges[cur][i] == -1)
                continue;
            ans = min(ans, edges[cur][i] + tsp((mask | 1 << i), i, n, edges, dp));
        }
    }

    /*cout << "tsp called with mask=" << mask << ", cur=" << cur << " returned " << ans << endl;*/
    return dp[cur][mask] = ans;

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vvll edges(n, vll(n, -1));
    while (m--) {
        int u, v, d;
        cin >> u >> v >> d;
        u--;
        v--;
        edges[u][v] = d;
        edges[v][u] = d;
    }

    vvll dp(n, vll(1 << n, -1));
    ll ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        ans = min(ans, tsp(1 << i, i, n, edges, dp));
    }
    cout << ans << endl;
}

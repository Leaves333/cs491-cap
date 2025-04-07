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

struct matrix {
    int arr[20][1 << 20];
};

// mask: bitmask of visited cities
// cur: current city we're at
// n: total number of cities
// edges: adjacency matrix of distances
// dp: memoization of states
int tsp(int mask, int cur, int n, const vvi &edges, matrix &dp) {

    // base case: all cities visited
    if (mask == (1 << n) - 1)
        return 0;

    // this case is in our dp
    if (dp.arr[cur][mask] != -1)
        return dp.arr[cur][mask];

    int ans = INT_MAX;

    // try visiting every unvisited city
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) == 0) {
            if (edges[cur][i] == INT_MAX)
                continue;
            ans = min(ans, edges[cur][i] + tsp((mask | 1 << i), i, n, edges, dp));
        }
    }

    return dp.arr[cur][mask] = ans;

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vvi edges(n, vi(n, INT_MAX));
    while (m--) {
        int u, v, d;
        cin >> u >> v >> d;
        u--;
        v--;
        edges[u][v] = d;
        edges[v][u] = d;
    }

    // floyd-warshall to generate distance array
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (edges[i][k] < INT_MAX && edges[k][j] < INT_MAX)
                    edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j]); 
            }
        }
    }

    /*vvi dp(n, vi(1 << n, -1));*/
    matrix dp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1 << n; j++) {
            dp.arr[i][j] = -1;
        }
    }
    
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        ans = min(ans, tsp(1 << i, i, n, edges, dp));
    }
    cout << ans << endl;
}

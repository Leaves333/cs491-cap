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

vvi dp(20, vi(1 << 20));
int n;

int tsp(const vvi &costs, const int &mx, int cur, int state) {
    
    if (dp[cur][state] > 0)
        return dp[cur][state];
    if (state == mx)
        return 0; // return home

    int minleft = INT_MAX;
    int bit = 1;
    for (int i = 0; i < n; ++i) {
        if ((state & bit) == 0) { // i not visited
            minleft =
                min(minleft, costs[cur][i] + tsp(costs, mx, i, state | bit));
        }
        bit <<= 1;
    }

    return dp[cur][state] = minleft;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m;
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

    const int mx = (1 << n) - 1;
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        ans = min(ans, tsp(edges, mx, i, 1 << i));
    }
    cout << ans << endl;
}

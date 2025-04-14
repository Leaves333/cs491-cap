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

void dfs(int x, const vvi &edges, vi &ordering) {
    for (auto dest : edges[x]) {
        dfs(dest, edges, ordering);
    }
    ordering.push_back(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {

        // grab input
        int n, m, k;
        cin >> n >> m >> k;

        vvi edges(n + 1);
        for (int i = 1; i <= n; i++) {
            int k; cin >> k;
            while (k--) {
                int x; cin >> x;
                edges[i].push_back(x);
            }
        }

        vvi denoise(n + 1);
        while (m--) {
            int u, v;
            cin >> u >> v;
            denoise[u].push_back(v);
        }

        // dp[i] stores number of denoisings needed starting at i
        vi dp(n + 1, -1);
        while (k--) {
            int x; cin >> x;
            dp[x] = 0;
        }

        // get postorder traversal through graph
        vi ordering;
        dfs(1, edges, ordering);

        // do the dp
        for (auto x : ordering) {

            // ignore leaf nodes
            if (edges[x].size() == 0)
                continue;

            // if no denoising is done, consider all children
            bool all_children_valid = true;
            int children_sum = 0;
            for (auto child : edges[x]) {
                if (dp[child] == -1)
                    all_children_valid = false;
                children_sum += dp[child];
            }

            if (all_children_valid)
                dp[x] = children_sum;

            // if denoising is done, consider the one child
            for (auto child : denoise[x]) {
                if (dp[child] == -1)
                    continue;
                if (dp[x] == -1)
                    dp[x] = dp[child] + 1;
                else
                    dp[x] = min(dp[x], dp[child] + 1);
            }

        }

        cout << dp[1] << endl;

    }

}

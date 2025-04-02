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
    for (auto dest : edges[x])
        dfs(dest, edges, ordering);
    ordering.push_back(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vvi edges(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        edges[min(x, y)].push_back(max(x, y));
    }

    vll values(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> values[i];
    }

    vi ordering;
    dfs(1, edges, ordering);

    vll dp(n + 1);
    for (int x : ordering) {
        ll first = 0, second = values[x];
        for (auto child : edges[x]) {
            first += dp[child];
            for (auto child_of_child : edges[child]) {
                second += dp[child_of_child];
            }
        }
        dp[x] = max(first, second);
    }

    /*for (int i = 0; i < n + 1; i++) {*/
    /*    cout << i << " : " << dp[i] << endl;*/
    /*}*/
    /*cout << endl;*/

    cout << dp[1] << endl;

}

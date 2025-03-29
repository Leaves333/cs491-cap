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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, t;
    cin >> n >> t;
    vi a(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // dp[i][j] stores max value when only first i items are considered
    // with capacity j
    vvi dp(n + 1, vi(t + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= t; j++) {
            dp[i][j] = dp[i-1][j];
            if (a[i-1] <= j) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-a[i-1]] + v[i-1]);
            }
        }
    }

    cout << dp[n][t] << endl;
}

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

const int MOD = 998244353;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, w;
    int dollars, cents;
    char dot;

    cin >> n >> dollars >> dot >> cents;
    w = dollars * 100 + cents;

    vll values(n);
    for (int i = 0; i < n; i++) {
        cin >> dollars >> dot >> cents;
        values[i] = dollars * 100 + cents;
    }

    // dp[i][j] stores number of ways to get j considering first i
    vll dp(w + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= w; j++) {
            if (j >= values[i])
                dp[j] += dp[j-values[i]];
            dp[j] %= MOD;
        }
    }

    cout << dp[w] << endl;
}

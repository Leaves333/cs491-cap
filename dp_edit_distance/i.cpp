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

    string a, b;
    cin >> a >> b;
    vvi dp(a.length() + 1, vi(b.length() + 1, INT_MAX));
    for (int i = 0; i <= a.length(); i++) {
        dp[i][0] = i;
    }
    for (int i = 0; i <= b.length(); i++) {
        dp[0][i] = i;
    }

    for (int i = 1; i <= a.length(); i++) {
        for (int j = 1; j <= b.length(); j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
            }
            int smol = dp[i-1][j];
            smol = min(smol, dp[i][j-1]);
            smol = min(smol, dp[i-1][j-1]);
            dp[i][j] = min(dp[i][j], 1 + smol);
        }
    }

    cout << dp[a.length()][b.length()] << endl;

}

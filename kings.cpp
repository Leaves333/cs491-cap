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

int n, m, k;

// returns true if you can place kings
bool is_good(int prev, int cur) {
    bool last = false;
    for (int i = 0; i < n; i++) {
        for (int j = max(0, i-1); j < min(n, i+1); j++) {
            if ((cur & (1 << i)) && (prev & (1 << j)))
                return false;
        }

        if (cur & (1 << i)) {
            if (last)
                return false;
            last = true;
        } else {
            last = false;
        }
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;

    // dp[i][k][s] stores considering first i rows, k kings placed, last like looks like s
    vector<vector<map<int, int>>> dp(m, vector<map<int, int>>(k+1));
    for (int mask = 0; mask < (1 << n); mask++) {
        bool prev = false;
        bool good = true;
        int popcount = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (prev) {
                    good = false;
                    break;
                }
                prev = true;
                popcount++;
            } else {
                prev = false;
            }
        }

        if (good) {
            dp[0][popcount][mask] = 1;
            
            for (int i = 10; i >= 0; i--) {
                cout << (bool) (mask & (1 << i));
            }
            cout << endl;
        }
    }

    for (int row = 1; row < m; row++) {
        for (int cur_row = 0; cur_row < (1 << n); cur_row++) {

            // check all possible ways to place kings?
            for (int kings = 0; kings <= k; kings++) {
                for (const auto &[prev_row, prev_count] : dp[row - 1][kings]) {
                    if (!is_good(prev_row, cur_row))
                        continue;
                    if (kings + __builtin_popcount(cur_row) > k)
                        continue;
                    dp[row][kings + __builtin_popcount(cur_row)][cur_row] += prev_count;
                }
            }

        }
    }

    ll ans = 0;
    for (const auto &[row, count] : dp[m-1][k]) {
        cout << "row=";
        for (int i = 10; i >= 0; i--) {
            cout << (bool) (row & (1 << i));
        }
        cout << ", count=" << count << endl;
        ans += count;
    }
    cout << ans << endl;
}

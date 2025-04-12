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

struct item {
    ll cost, value;
};

const ll THRESH = 100000;

ll solve(ll n, const vvll &dp, map<int, ll> &memo) {
    cout << "solve called with n=" << n << endl;
    if (n <= THRESH) {
        return dp.back()[n];
    }
    if (memo.count(n)) {
        return memo[n];
    }
    ll ans = LLONG_MAX;
    int half = (n / 2) - 500;
    for (int i = 0; i <= 1001; i++) {
        ans = max(ans, solve(n - half, dp, memo) + solve(half, dp, memo));
        half++;
    }
    return memo[n] = ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, s;
    cin >> n >> s;
    vector<item> items;
    item best_item = {100000000, 1};
    for (int i = 0; i < n; i++) {
        int w, v;
        cin >> w >> v;
        items.push_back({w, v});
        if ((double) v / w > (double) best_item.value / best_item.cost)
            best_item = {w, v};
    }

    /*ll copies = max(0ll, (s - 100000) / best_item.cost);*/
    /*ll ans = copies * best_item.value;*/
    /*s -= copies * best_item.cost;*/

    cout << "calculating dp..." << endl;
    vvll dp(n + 1, vll(THRESH + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= THRESH; j++) {
            dp[i][j] = dp[i-1][j];
            if (items[i-1].cost <= j) {
                dp[i][j] = max(dp[i][j], dp[i][j-items[i-1].cost] + items[i-1].value);
            }
        }
    }
    cout << "done !" << endl;

    map<int, ll> memo;
    cout << solve(s, dp, memo) << endl;

}

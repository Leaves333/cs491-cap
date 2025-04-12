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

// dp[pos][prev][small][has_495]
ll dp[20][100][2][2];

ll solve(int pos, int prev, bool small, bool has_495, const vi &digits) {

    if (pos >= digits.size())
        return has_495;

    if (dp[pos][prev][small][has_495] != -1)
        return dp[pos][prev][small][has_495];

    ll ans = 0, limit = 0;
    if (!small)
        limit = digits[pos];
    else
        limit = 9;

    for (int i = 0; i <= limit; i++) {
        int new_prev = (prev * 10) + i;
        new_prev %= 100;
        bool new_small = (i != limit) || small;
        bool new_has_495 = ((prev == 49) && (i == 5)) || has_495;
        ans += solve(pos + 1, new_prev, new_small, new_has_495, digits);
    }
    return dp[pos][prev][small][has_495] = ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll l, r;
    cin >> l >> r;
    l--;

    vi l_digits, r_digits;
    while (l > 0) {
        l_digits.push_back(l % 10);
        l /= 10;
    }
    reverse(l_digits.begin(), l_digits.end());

    while (r > 0) {
        r_digits.push_back(r % 10);
        r /= 10;
    }
    reverse(r_digits.begin(), r_digits.end());

    memset(dp, -1ll, sizeof(dp));
    ll high = solve(0, 0, false, false, r_digits);
    memset(dp, -1ll, sizeof(dp));
    ll low = solve(0, 0, false, false, l_digits);

    cout << high - low << endl;

}

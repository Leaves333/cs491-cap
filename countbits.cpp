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

const ll MOD = 1000000007;

ll solve(ll l, ll r) {

    r++; // r is exclusive
    ll ans = 0;
    for (int i = 0; i <= 60; i++) {

        ll size = 1ll << (i + 1);

        ll lower_bound = (l / size) + (l % size != 0);
        ll upper_bound = (r / size);

        if (lower_bound <= upper_bound) {

            // add whole chunks
            ans += ((upper_bound - lower_bound) % MOD) * ((size / 2) % MOD);
            ans %= MOD;

            // add left side
            ll extra_on_left = (lower_bound * size) - l;
            ll bits_on_left = min(extra_on_left, size / 2);
            ans += bits_on_left % MOD;
            ans %= MOD;

            // add right side
            ll extra_on_right = r - (upper_bound * size);
            ll bits_on_right = max(0ll, extra_on_right - (size / 2));
            ans += bits_on_right % MOD;
            ans %= MOD;

        } else {

            ll middle_bound = (upper_bound * size) + (size / 2);
            ll bits_to_add = max(0ll, min(r - middle_bound, r - l));
            ans += bits_to_add % MOD;
            ans %= MOD;

        }

    }
    return ans % MOD;
}

ll brute_force(ll l, ll r) {
    ll ans = 0;
    for (ll i = l; i <= r; i++) {
        ans += __builtin_popcountll(i);
        ans %= MOD;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        ll l, r;
        cin >> l >> r;
        cout << solve(l, r) << endl;
    }
}

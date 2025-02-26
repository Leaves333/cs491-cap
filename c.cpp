#include <algorithm>
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

    cout << "solve called with " << l << " " << r << endl;

    ll ans = 0;
    for (int i = 0; i <= 61; i++) {

        ll size = 1ll << (i + 1);

        ll lower_bound = l / size;
        ll upper_bound = (r / size) + 1;

        cout << "for size = " << size << " => " << i << "... " << endl;

        cout << "lower_bound = " << lower_bound << ", upper_bound=" << upper_bound << endl;

        // add complete segments
        ans += ((upper_bound - lower_bound - 1) % MOD) * (size / 2);
        ans %= MOD;
        cout << upper_bound - lower_bound - 1 << " complete segments" << endl;

        // handle edge case
        if (upper_bound - lower_bound - 1 == 0) {
            int smol = max(l, (lower_bound * size) + size / 2);
            int big = min(r, (lower_bound * size) + size / 2);
            // TODO: wait this isn't working
            continue;
        }

        // add stuff on left
        ll stuff_on_left = (lower_bound + 1) * size - l;
        ans += min(stuff_on_left, size / 2);
        ans %= MOD;
        cout << min(stuff_on_left, size / 2) << " on left" << endl;

        // add stuff on right
        ll stuff_on_right = (r - (upper_bound * size));
        ans += max(0ll, stuff_on_right - (size / 2));
        ans %= MOD;
        cout << max(0ll, stuff_on_right - (size / 2)) << " on right" << endl;

        cout << endl;

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

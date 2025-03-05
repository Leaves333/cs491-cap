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

ll brute_force(ll n, ll k) {
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += k % i;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, k;
    cin >> n >> k;

    ll ans = n * k;

    ll l = 1;
    while (k / l != 0 && l <= n) {
        ll r = k / (k / l);
        r = min(n, r);
        ans -= ((r - l + 1) * (l + r) / 2) * (k / l);
        l = r + 1;
    }

    cout << ans << endl;
}

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

    int n; cin >> n;

    // lcm (a, b) = ab / gcd(a, b)
    // lcm (a, b) * gcd(a, b) = ab
    // solve in n sqrt n ???

    vll dist(n + 1, LLONG_MAX);
    ll ans = 0;
    for (ll i = 1; i < n; i++) {
        int multi = 2;
        while (true) {
            ll prod = i * multi;
            bool can_divide = prod % (multi - 1) == 0;
            bool in_range = prod / (multi - 1) <= n;
            if (can_divide && in_range)
                break;
            multi++;
        }
        /*cout << i << " -> " << multi << endl;*/
        dist[i] = i * multi;
        ans += dist[i];
    }

    cout << ans << endl;
}

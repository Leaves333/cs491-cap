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

    ll n, s;
    cin >> n >> s;
    vll nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vll psum(n + 1);
    for (int i = 0; i < n; i++) {
        psum[i + 1] = psum[i] + nums[i];
    }

    multiset<ll> seen;
    seen.insert(0);
    ll ans = 0;
    for (int i = 1; i < n + 1; i++) {
        auto up = seen.upper_bound(psum[i] - s);
        int dist = distance(up, seen.end());
        ans += dist;
        seen.insert(psum[i]);
    }

    cout << ans << endl;
}

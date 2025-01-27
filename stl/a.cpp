#include <climits>
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
    vll psum(n + 1);
    for (int i = 1; i < n + 1; i++) {
        ll x; cin >> x;
        psum[i] = psum[i - 1] + x;
    }

    ll ans = LLONG_MIN;
    ll smol = psum[0];
    for (int i = 1; i < n + 1; i++) {
        ans = max(ans, psum[i] - smol);
        smol = min(smol, psum[i]);
    }
    cout << max(0ll, ans) << endl;
}

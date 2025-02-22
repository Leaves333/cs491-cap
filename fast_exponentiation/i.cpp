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

ll pow_mod(ll x, ll n, ll m) {
    if (n == 0) return 1;
    ll t = pow_mod(x, n / 2, m);
    if (n % 2 == 1) {
        return (((t * t) % m) * x) % m;
    } else {
        return (t * t) % m;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        cout << pow_mod(n % MOD, k, MOD) << endl;
    }
}

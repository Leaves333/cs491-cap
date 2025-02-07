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

    ll n, k;
    cin >> n >> k;
    int first, second;
    cin >> first >> second;

    map<int, ll> a;
    map<int, ll> b;
    for (int i = 0; i < first; i++) {
        int x; cin >> x;
        a[x]++;
    }
    for (int i = 0; i < second; i++) {
        int x; cin >> x;
        b[x]++;
    }

    ll ans = 0;
    for (int sum = 200; sum > 1; sum--) {
        for (int i = 0; i < sum; i++) {
            ll j = sum - i;
            ll potential_pairs = a[i] * b[j];
            ll num_problems = min(k, potential_pairs);
            ans += num_problems * sum;
            k -= num_problems;
        }
    }

    cout << ans << endl;
}

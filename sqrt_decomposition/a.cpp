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

    ll n, q;
    cin >> n >> q;
    vll nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int s = ceil(sqrt(n));
    vvll precomp(s + 1, vll(s + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= s; j++) {
            precomp[j][i % j] += nums[i];
        }
    }

    while (q--) {
        int m, p;
        cin >> m >> p;
        p--;

        if (m <= s) {
            // we have it precomputed
            cout << precomp[m][p] << endl;
        } else {
            // do the calculation
            ll ans = 0;
            for (int i = p; i < n; i += m) {
                ans += nums[i];
            }
            cout << ans << endl;
        }
    }
}

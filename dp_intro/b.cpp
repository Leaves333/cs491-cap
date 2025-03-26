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
    vll a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    // stores the max if the student at a/b[i] is chosen
    vll dp_a(n);
    vll dp_b(n);

    ll ans = 0;
    if (n > 0) {
        dp_a[0] = a[0];
        dp_b[0] = b[0];
        ans = max(a[0], b[0]);
    }
    if (n > 1) {
        dp_a[1] = max(dp_a[0], a[1] + b[0]);
        dp_b[1] = max(dp_b[0], b[1] + a[0]);
        ans = max(dp_a[1], ans);
        ans = max(dp_b[1], ans);
    }

    for (int i = 2; i < n; i++) {
        dp_a[i] = max(dp_b[i-1], dp_a[i-2]) + a[i];
        dp_a[i] = max(dp_a[i], dp_a[i-1]);
        dp_b[i] = max(dp_a[i-1], dp_b[i-2]) + b[i];
        dp_b[i] = max(dp_b[i], dp_b[i-1]);
        ans = max(ans, dp_a[i]);
        ans = max(ans, dp_b[i]);
    }

    cout << ans << endl;

}

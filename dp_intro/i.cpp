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
    vi nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vll dp_skip(n, LLONG_MIN);
    vll dp_no_skip(n, LLONG_MIN);
    dp_no_skip[0] = nums[0];
    for (int i = 1; i < n; i++) {
        dp_no_skip[i] = max(dp_no_skip[i-1], dp_skip[i-1]) + nums[i];
        dp_skip[i] = max(dp_no_skip[i], dp_no_skip[i-1]);
    }

    cout << dp_no_skip[n-1] << endl;

}

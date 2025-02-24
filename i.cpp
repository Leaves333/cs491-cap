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

// helper function to quickly compute log2(i)
int log2_floor(ll i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
    // builtin clz is counting the number of leading zeroes
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vi nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int l, r, s;
    cin >> l >> r >> s;
    l--; r--;

    // time to build a sparse tree
    // preprocessing for sparse tree is in n log(n)
    const int K = 20; // needs to fulfill K >= log_2 n
    int st[K + 1][n]; // n is second for cache optimization
    
    // move nums into sparse tree
    copy(nums.begin(), nums.end(), st[0]);

    for (int i = 1; i <= K; i++) // for each interval size 2^K
        for (int j = 0; j + (1 << i) <= n; j++) // for each starting point j
            st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]); // compute maximum of the two intevals

    // time to answer queries
    ll ans = 0;
    while (m--) {

        int i = log2_floor(r - l + 1);
        int maximum = max(st[i][l], st[i][r - (1 << i) + 1]);
        ans += maximum;

        // generate the next range
        l += s;
        l %= n;
        r += s;
        r %= n;
        if (l > r)
            swap(l, r);
    }

    cout << ans << endl;
}

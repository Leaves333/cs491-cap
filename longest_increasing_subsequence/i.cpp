#include <algorithm>
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

    vi d(n + 1, INT_MAX); // dp for finding size of lis
    vi idx(n + 1, -1); // index of each element in d
    vi p(n + 1, -1); // index of previous element for sequence ending at i
    d[0] = INT_MIN;
    for (int i = 0; i < n; i++) {
        // binary search for first element greater than x
        int l = upper_bound(d.begin(), d.end(), nums[i]) - d.begin();
        if (d[l-1] < nums[i] && nums[i] < d[l]) {
            d[l] = nums[i];
            idx[l] = i;
            p[i] = idx[l-1];
        }

    }

    int ans = 0, pos = -1;
    for (int i = 1; i <= n; i++) {
        if (d[i] < INT_MAX) {
            ans = i;
            pos = idx[i];
        }
    }

    cout << ans << endl;

    vi subseq;
    while (pos != -1) {
        subseq.push_back(nums[pos]);
        pos = p[pos];
    }
    reverse(subseq.begin(), subseq.end());

    for (auto x : subseq) {
        cout << x << " ";
    }
    cout << endl;
}

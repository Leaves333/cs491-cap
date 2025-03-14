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

    vi d; // dp for finding size of lis
    vi idx; // index of each element in d
    vi p(n); // index of previous element for sequence ending at i
    for (int i = 0; i < n; i++) {
        if (nums[i] > d.back()) {
            d.push_back(nums[i]);
            idx.push_back(i);
        }

        // binary search for first element greater than x
        int l = upper_bound(d.begin(), d.end(), nums[i]) - d.begin();
        if (d[l-1] < nums[i] && nums[i] < d[l]) {
            d[l] = nums[i];
            idx[l] = i;
            p[i] = l;
        }

    }

    cout << d.size() << endl;

    cout << endl;
}

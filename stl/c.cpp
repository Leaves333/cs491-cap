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

    int n, m;
    cin >> n >> m;
    vi nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int lastl = 0, lastr = -1;
    multiset<int> vals;
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        for (int i = lastr + 1; i <= r; i++) {
            vals.insert(nums[i]);
        }
        for (int i = lastl; i < l; i++) {
            vals.erase(vals.find(nums[i]));
        }
        cout << *(--vals.end()) << endl;
        lastl = l;
        lastr = r;
    }
}

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

    map<int, int> count;
    int best_num = -1;
    int best_idx = -1;
    for (int i = 0; i < n; i++) {
        count[nums[i]] = count[nums[i]-1] + 1;
        if (count[nums[i]] > count[best_num]) {
            best_num = nums[i];
            best_idx = i;
        }
    }

    vi ans;
    int k = best_num;
    for (int i = best_idx; i >= 0; i--) {
        if (nums[i] == k) {
            ans.push_back(i + 1);
            k--;
        }
    }

    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << endl;

}

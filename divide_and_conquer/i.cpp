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

ll ans = 0;
void merge_sort(vll &nums, const ll s) {

    if (nums.size() <= 1)
        return;

    int mid = nums.size() / 2;
    vll left(nums.begin(), nums.begin() + mid);
    vll right(nums.begin() + mid, nums.end());

    merge_sort(left, s);
    merge_sort(right, s);

    int l = 0, r = 0;
    while (r < right.size()) {
        while (l < left.size() && right[r] - left[l] >= s) {
            l++;
        }
        if (l >= left.size()) {
            r++;
            continue;
        }
        ans += left.size() - l;
        r++;
    }

    merge(left.begin(), left.end(), right.begin(), right.end(), nums.begin());

}

int main() {

    cin.tie(0)->sync_with_stdio(0);

    ll n, s;
    cin >> n >> s;
    vll nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vll psum(n + 1);
    for (int i = 0; i < n; i++) {
        psum[i + 1] = psum[i] + nums[i];
    }

    ans = 0;
    merge_sort(psum, s);
    cout << ans << endl;

}

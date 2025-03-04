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

ll lowbit(ll x) {
    return x & -x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int sqrt_n = 1;
    while (sqrt_n * sqrt_n < n)
        sqrt_n++;

    vll nums(n + 1);
    vll sqrt_nums(sqrt_n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        sqrt_nums[i / sqrt_n] += nums[i];
    }

    while (m--) {
        int l, r;
        cin >> l >> r;

        int low = (l / sqrt_n) + !(l % sqrt_n == 0);
        int high = (r / sqrt_n);

        cout << "l=" << l << ", ";
        cout << "r=" << r << endl;
        cout << "low=" << low << ", ";
        cout << "high=" << high << endl;

        ll ans = 0;
        for (int i = low; i < high; i++) {
            cout << "adding sqrt_nums[" << i << "]" << endl;
            ll cur = sqrt_nums[i];
            ll exp = lowbit(l ^ i);
            if (exp % 2 == 1)
                cur *= -1;
            ans += cur;
        }

        for (int i = l; i < low * sqrt_n; i++) {
            cout << "adding nums[" << i << "]" << endl;
            ll cur = nums[i];
            ll exp = lowbit(l ^ (i / sqrt_n));
            if (exp % 2 == 1)
                cur *= -1;
            ans += cur;
        }

        for (int i = high * sqrt_n; i <= r; i++) {
            cout << "adding nums[" << i << "]" << endl;
            ll cur = nums[i];
            ll exp = lowbit(l ^ (i / sqrt_n));
            if (exp % 2 == 1)
                cur *= -1;
            ans += cur;
        }

        ll accurate_sum = 0;
        for (int i = l; i <= r; i++) {
            ll cur = nums[i];
            ll exp = lowbit(l ^ (i / sqrt_n));
            if (exp % 2 == 1)
                cur *= -1;
            accurate_sum += cur;
        }

        cout << ans << endl;
        cout << "should be " << accurate_sum << endl;
        cout << endl;
    }
}

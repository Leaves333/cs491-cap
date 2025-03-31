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
    vll nums(n);
    vector<string> operators(n - 1);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    for (int i = 0; i < n-1; i++) {
        cin >> operators[i];
    }

    // stores max of chain starting at i and ending at j
    vvll dp(n, vll(n));
    for (int i = 0; i < n; i++) {
        dp[i][i] = nums[i];
    }
}

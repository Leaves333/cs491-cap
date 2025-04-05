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

    int t; cin >> t;
    while (t--) {
        int n; cin >> t;
        vi nums(n);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
    }

    // observations:
    // n is always pos
    // k-1 +, k+ => 2 2
    // k-1 -, k+ => 1 2
    // k-1 +, k- => 1 0
    // k-1 -, k- => 0 0
    //
    // 1  2 -3  4  5
    // 4  4  2  5  5
    //
    // 1  2 -3  4
    // 3  3  1  4
}

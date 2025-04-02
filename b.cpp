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
        int k, d;
        string s;
        cin >> k >> d >> s;

        // substring up to i, j conversions
        vvi dp(s.length(), vi(k));

        for (int i = 0; i < s.length(); i++) {
            for (int j = 0; j < k; j++) {
                // convert this???
                // don't convert this
            }
        }
    }
}

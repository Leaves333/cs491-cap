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

        vi psum(s.length() + 1);
        for (int i = 0; i < s.length(); i++) {
            psum[i + 1] = (s[i] == '0');
        }
        for (int i = 1; i < psum.size(); i++) {
            psum[i] += psum[i - 1];
        }

        /*cout << "here's psum:" << endl;*/
        /*for (int i = 0; i < psum.size(); i++) {*/
        /*    cout << psum[i] << " ";*/
        /*}*/
        /*cout << endl;*/

        // substring up to i, j conversions
        vvi dp(s.length() + 1, vi(k + 1));

        for (int i = d; i <= s.length(); i++) {
            for (int j = 0; j <= k; j++) {

                // convert this???
                int target_j = j-(psum[i]-psum[i-d]);
                if (target_j >= 0)
                    dp[i][j] = max(dp[i][j], dp[i-d][target_j] + 1);

                // don't convert this
                dp[i][j] = max(dp[i][j], dp[i-1][j]);

            }
        }

        /*cout << "here's dp: " << endl;*/
        /*for (int j = 0; j <= k; j++) {*/
        /*    for (int i = 0; i <= s.length(); i++) {*/
        /*        cout << dp[i][j] << " ";*/
        /*    }*/
        /*    cout << endl;*/
        /*}*/

        int ans = 0;
        for (auto row : dp) {
            for (auto x : row) {
                ans = max(ans, x);
            }
        }
        cout << ans << endl;
    }
}

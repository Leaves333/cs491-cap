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
    string s; cin >> s;

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int l = i, r = i;
        while (true) {
            if (l < 0 || r >= n) break;
            if (s[l] != s[r]) break;
            ans++;
            l--;
            r++;
        }
        l = i, r = i + 1;
        while (true) {
            if (l < 0 || r >= n) break;
            if (s[l] != s[r]) break;
            ans++;
            l--;
            r++;
        }
    }
    cout << ans << endl;
}

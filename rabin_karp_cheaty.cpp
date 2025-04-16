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

    string s; cin >> s;
    vector<unordered_map<string, int>> count(s.length() + 1);

    for (int i = 0; i < s.length(); i++) {
        string substr = "";
        for (int j = i; j < s.length(); j++) {
            substr += s[j];
            count[substr.length()][substr]++;
        }
    }

    ll ans = 0;
    for (int i = 0; i < s.length() + 1; i++) {
        for (const auto &[key, value] : count[i]) {
            ans += value * (value - 1);
        }
    }
    cout << ans / 2 << endl;

}

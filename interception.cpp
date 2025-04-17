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

vector<char> prefix_function(const string s, const int len) {

    int n = s.length();
    vi pi;
    pi.push_back(0);
    vector<char> ans;

    for (int i = len; i < n; i++) {
        int j = pi.back();
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi.push_back(j);
        ans.push_back(s[i]);

        if (j >= len) {
            for (int k = 0; k < len; k++) {
                pi.pop_back();
                ans.pop_back();
            }
        }
    }

    return ans;

}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t;
    cin >> s >> t;
    string search = t + "." + s;

    auto char_vector = prefix_function(search, t.length());
    string ans = "";
    for (int i = 1; i < char_vector.size(); i++) {
        ans += char_vector[i];
    }

    cout << ans << endl;

}

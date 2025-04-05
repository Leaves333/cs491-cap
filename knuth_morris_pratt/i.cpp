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

vi prefix_function(string s) {
    int n = s.length();
    vi pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string a, b;
    cin >> a >> b;

    string s = b + "." + a;
    vi p = prefix_function(s);
    int ans = 0;
    for (int i = b.length() + 1; i < s.length(); i++) {
        if (p[i] >= b.length())
            ans++;
    }
    cout << ans << endl;
}

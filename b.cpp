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
    vector<string> words(n);
    set<string> unique_words;
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        unique_words.insert(words[i]);
    }

    map<string, map<string, ll>> d;
    for (auto a : unique_words) {
        for (auto b : unique_words) {
            d[a][b] = LLONG_MAX;
            if (a[a.length() - 1] == b[0]) {
                d[a][b] = a.length();
            }
        }
    }

    for (auto k : unique_words) {
        for (auto a : unique_words) {
            for (auto b : unique_words) {
                if (d[a][k] < LLONG_MAX && d[k][b] < LLONG_MAX)
                    d[a][b] = min(d[a][b], d[a][k] + d[k][b]);
            }
        }
    }

    sort(words.begin(), words.end());
    bool good = true;
    ll ans = LLONG_MAX;
    while (good) {
        ll cur = words[words.size() - 1].length();
        bool possible_perm = true;
        for (int i = 0; i < words.size() - 1; i++) {
            if (d[words[i]][words[i+1]] == LLONG_MAX) {
                possible_perm = false;
                break;
            }
            cur += d[words[i]][words[i+1]];
        }
        if (possible_perm) {
            ans = min(ans, cur);
        }
        good = next_permutation(words.begin(), words.end());
    }

    cout << ans << endl;
}

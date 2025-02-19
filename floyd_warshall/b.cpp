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

vector<string> word_v;
int word_to_index(string s) {
    for (int i = 0; i < word_v.size(); i++) {
        if (word_v[i] == s)
            return i;
    }
    word_v.push_back(s);
    return word_v.size() - 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        word_to_index(words[i]);
    }

    ll d[n][n];
    for (int a = 0; a < word_v.size(); a++) {
        for (int b = 0; b < word_v.size(); b++) {
            d[a][b] = LLONG_MAX;
            if (word_v[a][word_v[a].length() - 1] == word_v[b][0]) {
                d[a][b] = word_v[a].length();
            }
        }
    }

    for (int k = 0; k < word_v.size(); k++) {
        for (int a = 0; a < word_v.size(); a++) {
            for (int b = 0; b < word_v.size(); b++) {
                if (d[a][k] < LLONG_MAX && d[k][b] < LLONG_MAX)
                    d[a][b] = min(d[a][b], d[a][k] + d[k][b]);
            }
        }
    }


    vi nums;
    for (int i = 0; i < word_v.size(); i++) {
        nums.push_back(i);
    }

    bool good = true;
    ll ans = LLONG_MAX;
    while (good) {
        ll cur = word_v[nums[nums.size() - 1]].length();
        bool possible_perm = true;
        for (int i = 0; i < nums.size() - 1; i++) {
            if (d[nums[i]][nums[i+1]] == LLONG_MAX) {
                possible_perm = false;
                break;
            }
            cur += d[nums[i]][nums[i+1]];
        }
        if (possible_perm) {
            ans = min(ans, cur);
        }
        good = next_permutation(nums.begin(), nums.end());
    }

    cout << ans << endl;
}

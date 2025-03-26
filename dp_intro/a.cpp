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

vector<string> ans;
bool found;
void dp(string cur_word, int idx, const vector<string> &tokens, const set<string> &words, vector<string> &stk) {

    if (found)
        return;

    // base case
    if (idx >= tokens.size()) {
        if (cur_word == "") {
            found = true;
            ans = stk;
        }
        return;
    }

    cur_word += tokens[idx];
    if (words.count(cur_word)) {
        stk.push_back(cur_word);
        dp("", idx + 1, tokens, words, stk);
        stk.pop_back();
    }

    dp(cur_word, idx + 1, tokens, words, stk);

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    set<string> words;
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        words.insert(s);
    }

    vector<string> tokens(n);
    for (int i = 0; i < n; i++) {
        cin >> tokens[i];
    }

    ans.clear();
    found = false;

    vector<string> stk;
    dp("", 0, tokens, words, stk);
    
    if (found) {
        for (string s : ans) {
            cout << s << " ";
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
}

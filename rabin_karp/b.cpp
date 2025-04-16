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

// constants for hashing
const int MOD = 1e9 + 9;
const int p = 31, q = 53;
const int N = 500001;

// precompute powers of p and q
vll p_pow(N);
vll q_pow(N);
vll p_inverse(N);
vll q_inverse(N);

ll pow_mod(ll x, ll n) {
    if (n <= 0)
        return 1;
    ll t = pow_mod(x, n / 2);
    if (n % 2 == 1)
        return (((t * t) % MOD) * x) % MOD;
    else
        return (t * t) % MOD;
}

ll get_p_hash(string s) {
    ll p_hash = 0;
    for (int i = 0; i < s.length(); i++) {
        p_hash += (s[i] - 'A' + 1) * p_pow[i];
        p_hash %= MOD;
    }
    return p_hash;
}

ll get_q_hash(string s) {
    ll q_hash = 0;
    for (int i = 0; i < s.length(); i++) {
        q_hash += (s[i] - 'A' + 1) * q_pow[i];
        q_hash %= MOD;
    }
    return q_hash;
}

ll hashify(string s) {
    ll p_hash = 0, q_hash = 0;
    for (int i = 0; i < s.length(); i++) {
        p_hash += (s[i] - 'A' + 1) * p_pow[i];
        q_hash += (s[i] - 'A' + 1) * q_pow[i];
        p_hash %= MOD;
        q_hash %= MOD;
    }
    return p_hash | (q_hash << 32);
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    // precompute powers of p and q
    p_pow[0] = 1;
    q_pow[0] = 1;
    for (int i = 1; i < N; i++) {
        p_pow[i] = (p_pow[i-1] * p) % MOD;
        q_pow[i] = (q_pow[i-1] * q) % MOD;
    }
    for (int i = 0; i < N; i++) {
        p_inverse[i] = pow_mod(p_pow[i], MOD - 2);
        q_inverse[i] = pow_mod(q_pow[i], MOD - 2);
    }

    int n, m;
    cin >> n >> m;
    unordered_set<ll> dictionary_words;
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        ll hash = get_p_hash(s) | (get_q_hash(s) << 32);
        dictionary_words.insert(hashify(s));
    }

    vector<string> tokens(n);
    for (int i = 0; i < n; i++) {
        cin >> tokens[i];
    }

    vector<ll> p_prefix(n + 1, 0);
    vector<ll> q_prefix(n + 1, 0);
    vector<ll> length(n + 1, 0);       // length of first n elements
    for (int i = 0; i < n; i++) {
        length[i + 1] = length[i] + tokens[i].length();

        // get hash of the token
        ll token_p = get_p_hash(tokens[i]);
        ll token_q = get_q_hash(tokens[i]);
        token_p = (token_p * p_pow[length[i]]) % MOD;
        token_q = (token_q * q_pow[length[i]]) % MOD;

        // add it to the previous hash
        p_prefix[i + 1] = (p_prefix[i] + token_p) % MOD;
        q_prefix[i + 1] = (q_prefix[i] + token_q) % MOD;
    }
    
    /*cout << "here's token hashes: " << endl;*/
    /*for (int i = 0; i < token_hashes.size(); i++) {*/
    /*    cout << i << " : " << hex << token_hashes[i] << dec << endl;*/
    /*}*/
    /*cout << "here's length" << endl;*/
    /*for (int i = 0; i < length.size(); i++) {*/
    /*    cout << i << " : " << length[i] << endl;*/
    /*}*/

    // dp[i] = -1 if no sol considering first i tokens
    // else dp[i] = prev
    vi dp(n + 1, -1);
    dp[0] = 0;
    vector<string> word(n + 1);
    for (int i = 0; i < n; i++) {

        string cur_word = "";

        // iterate backwards through tokens until we find a word with a solution
        for (int j = i; j >= 0; j--) {

            // update the word
            cur_word = tokens[j] + cur_word;

            // no words longer than 100 chars
            if (cur_word.length() > 100)
                break;

            // compute hash
            ll cur_p = (p_prefix[i + 1] - p_prefix[j]);
            if (cur_p < 0)
                cur_p += MOD;
            ll cur_q = (q_prefix[i + 1] - q_prefix[j]);
            if (cur_q < 0)
                cur_q += MOD;
            cur_p = (cur_p * p_inverse[length[j]]) % MOD;
            cur_q = (cur_q * q_inverse[length[j]]) % MOD;
            ll hash = cur_p | (cur_q << 32);

            // continue if no solution
            if (!dictionary_words.count(hash))
                continue;
            if (dp[j] < 0)
                continue;

            word[i + 1] = cur_word;
            dp[i + 1] = j;
            break;

        }
    }

    /*cout << "here's words:" << endl;*/
    /*for (int i = 0; i < word.size(); i++) {*/
    /*    cout << i << " : " << word[i] << endl;*/
    /*}*/
    /*cout << "here's dps:" << endl;*/
    /*for (int i = 0; i < dp.size(); i++) {*/
    /*    cout << i << " : " << dp[i] << endl;*/
    /*}*/
    /*cout << endl;*/

    if (dp.back() == -1) {
        cout << -1 << endl;
    } else {
        int cur = dp.size() - 1;
        vector<string> ans;
        while (cur != 0) {
            ans.push_back(word[cur]);
            cur = dp[cur];
        }
        reverse(ans.begin(), ans.end());
        for (auto x : ans) {
            cout << x << " ";
        }
        cout << endl;
    }

}

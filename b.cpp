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

ll hashify(string s) {
    ll p_hash = 0, q_hash = 0;
    for (int i = 0; i < s.length(); i++) {
        p_hash += (s[i] - 'a') * p_pow[i];
        q_hash += (s[i] - 'a') * q_pow[i];
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
    for (int i = 1; i <= N; i++) {
        p_pow[i] = (p_pow[i-1] * p) % MOD;
        q_pow[i] = (q_pow[i-1] * q) % MOD;
    }
    for (int i = 0; i <= N; i++) {
        p_inverse[i] = pow_mod(p_pow[i], MOD - 2);
        q_inverse[i] = pow_mod(q_pow[i], MOD - 2);
    }

    int n, m;
    unordered_set<ll> words;
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        words.insert(hashify(s));
    }

    vector<string> tokens(n);
    for (int i = 0; i < n; i++) {
        cin >> tokens[i];
    }

    // dp[i] = -1 if no sol considering first i tokens
    // else dp[i] = prev
    vi dp(n + 1, -1);
    vector<string> word(n + 1);
    for (int i = 0; i < n; i++) {
        ll cur_hash = 0;
        for (int j = i; j >= 0; j--) {
            ll cur_p = cur_hash % (1ll << 32);
            ll cur_q = cur_hash >> 32;

            ll token_hash = hashify(tokens[j]);
            ll token_p = token_hash % (1ll << 32);
            ll token_q = token_hash >> 32;

            cur_p *= p_pow[tokens[j].length()];
            cur_q *= q_pow[tokens[j].length()];
        }
    }

}

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

const int MOD = 1e9 + 9;

ll pow_mod(ll x, ll n) {
    if (n <= 0)
        return 1;
    ll t = pow_mod(x, n / 2);
    if (n % 2 == 1)
        return (((t * t) % MOD) * x) % MOD;
    else
        return (t * t) % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s; cin >> s;

    // constants for hashing
    const int p = 31, q = 53;

    // precompute powers of p and q
    vll p_pow(s.length() + 1);
    vll q_pow(s.length() + 1);
    vll p_inverse(s.length() + 1);
    vll q_inverse(s.length() + 1);

    p_pow[0] = 1;
    q_pow[0] = 1;
    for (int i = 1; i <= s.length(); i++) {
        p_pow[i] = (p_pow[i-1] * p) % MOD;
        q_pow[i] = (q_pow[i-1] * q) % MOD;
    }

    for (int i = 0; i <= s.length(); i++) {
        p_inverse[i] = pow_mod(p_pow[i], MOD - 2);
        q_inverse[i] = pow_mod(q_pow[i], MOD - 2);
    }

    // precompute hashes of prefixes
    vll p_prefix(s.length() + 1);
    vll q_prefix(s.length() + 1);
    for (int i = 0; i < s.length(); i++) {
        p_prefix[i + 1] = (p_prefix[i] + (s[i] - 'a' + 1) * p_pow[i]) % MOD;
        q_prefix[i + 1] = (q_prefix[i] + (s[i] - 'a' + 1) * q_pow[i]) % MOD;
    }

    // store how often each hash occurs
    unordered_map<ll, ll> count;
    for (int i = 0; i < p_prefix.size(); i++) {
        for (int j = i + 1; j < p_prefix.size(); j++) {

            ll p_hash = p_prefix[j] - p_prefix[i];
            ll q_hash = q_prefix[j] - q_prefix[i];
            if (p_hash < 0)
                p_hash += MOD;
            if (q_hash < 0)
                q_hash += MOD;

            p_hash = (p_hash * p_inverse[i]) % MOD;
            q_hash = (q_hash * q_inverse[i]) % MOD;
            ll hash = (p_hash | (q_hash << 32));
            count[hash]++;

        }
    }

    // compute number of pairs
    ll ans = 0;
    for (const auto &[key, value] : count) {
        ans += value * (value - 1);
    }
    cout << ans / 2 << endl;

}

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
const int p = 31;
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

    // precompute powers of p
    vll ppow(s.length() + 1);
    ppow[0] = 1;
    for (int i = 1; i <= s.length(); i++)
        ppow[i] = (ppow[i-1] * p) % MOD;

    // precompute hashes of prefixes
    vll hash_prefix(s.length() + 1);
    for (int i = 0; i < s.length(); i++)
        hash_prefix[i + 1] = (hash_prefix[i] + (s[i] - 'a' + 1) * ppow[i]) % MOD;

    // store how often each has occurs
    map<ll, ll> count;
    for (int i = 0; i < hash_prefix.size(); i++) {
        for (int j = i + 1; j < hash_prefix.size(); j++) {
            ll hash = hash_prefix[j] - hash_prefix[i];
            if (hash < 0)
                hash += MOD;
            ll inverse = pow_mod(ppow[i], MOD - 2);
            cout << "hash=" << hash << ", inverse=" << inverse << endl;
            hash = (hash * inverse) % MOD;
            count[hash]++;
        }
    }

    // compute number of pairs
    ll ans = 0;
    for (const auto &[key, value] : count) {
        cout << "hash=" << key << ", count=" << value << endl;
        ans += value * (value - 1);
    }
    cout << ans / 2 << endl;

}

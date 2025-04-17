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
const int N = 100001;

// precompute powers of p and q
vll p_pow(N);
vll q_pow(N);
vll p_inverse(N);
vll q_inverse(N);

// precompute hashes of prefixes
vll p_prefix;
vll q_prefix;
vll p_suffix;
vll q_suffix;

ll pow_mod(ll x, ll n) {
    if (n <= 0)
        return 1;
    ll t = pow_mod(x, n / 2);
    if (n % 2 == 1)
        return (((t * t) % MOD) * x) % MOD;
    else
        return (t * t) % MOD;
}

ll prefix_hash(int start, int len) {
    /*cout << "hashing prefix start=" << start << ", len=" << len << endl;*/

    ll p_hash = p_prefix[start + len] - p_prefix[start];
    if (p_hash < 0)
        p_hash += MOD;
    p_hash = (p_hash * p_inverse[start]) % MOD;
    /*cout << "\tprefix=" << p_hash << endl;*/

    ll q_hash = q_prefix[start + len] - q_prefix[start];
    if (q_hash < 0)
        q_hash += MOD;
    q_hash = (q_hash * q_inverse[start]) % MOD;

    return p_hash | (q_hash << 32);
}

ll suffix_hash(int start, int len) {
    /*cout << "hashing suffix start=" << start << ", len=" << len << endl;*/

    ll p_hash = p_suffix[start] - p_suffix[start + len];
    if (p_hash < 0)
        p_hash += MOD;
    p_hash = (p_hash * p_inverse[p_suffix.size() - start - len - 1]) % MOD;
    /*cout << "\tsuffix=" << p_hash << endl;*/

    ll q_hash = q_suffix[start] - q_suffix[start + len];
    if (q_hash < 0)
        q_hash += MOD;
    q_hash = (q_hash * q_inverse[q_suffix.size() - start - len - 1]) % MOD;

    return p_hash | (q_hash << 32);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    // precompute powers of p and q
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
    p_prefix.assign(s.length() + 1, 0);
    q_prefix.assign(s.length() + 1, 0);
    for (int i = 0; i < s.length(); i++) {
        p_prefix[i + 1] = (p_prefix[i] + (s[i] - 'a' + 1) * p_pow[i]) % MOD;
        q_prefix[i + 1] = (q_prefix[i] + (s[i] - 'a' + 1) * q_pow[i]) % MOD;
    }

    // and suffixes
    p_suffix.assign(s.length() + 1, 0);
    q_suffix.assign(s.length() + 1, 0);
    for (int i = s.length() - 1; i >= 0; i--) {
        p_suffix[i] = (p_suffix[i + 1] + (s[i] - 'a' + 1) * p_pow[s.length() - i - 1]) % MOD;
        q_suffix[i] = (q_suffix[i + 1] + (s[i] - 'a' + 1) * q_pow[s.length() - i - 1]) % MOD;
    }

    /*cout << "here's pprefix: " << endl;*/
    /*for (int i = 0; i < p_prefix.size(); i++) {*/
    /*    cout << i << " : " << p_prefix[i] << endl;*/
    /*}*/

    /*cout << "here's psuffix: " << endl;*/
    /*for (int i = 0; i < p_suffix.size(); i++) {*/
    /*    cout << i << " : " << p_suffix[i] << endl;*/
    /*}*/

    // binary search for len of longest palindrome
    ll ans = 0;
    for (int i = 0; i < s.length() - k; i++) {
        int low = 0, high = min(i, (int) s.length() - k - i);
        while (low < high) {
            int mid = low + (high - low + 1) / 2;
            if (prefix_hash(i - mid, mid) == suffix_hash(i + k, mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        ans += low;
    }

    cout << ans << endl;

}

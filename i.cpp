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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s; cin >> s;
    vll hash_prefix(s.length() + 1);
    vll ppow(s.length() + 1);
}

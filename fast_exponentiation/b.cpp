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

const ll MOD = 998244353;

vvll multiply_matrices(const vvll &first, const vvll &second) {
    vvll res(first.size(), vll(first.size()));
    for (int i = 0; i < first.size(); i++) {
        for (int j = 0; j < first[0].size(); j++) {
            ll sum = 0;
            for (int k = 0; k < first[0].size(); k++) {
                sum += first[i][k] * second[k][j];
                sum %= MOD;
            }
            res[i][j] = sum;
        }
    }
    return res;
}

vvll pow_mod(vvll base, ll exp) {

    if (exp == 0) {
        vvll identity(base.size(), vll(base.size()));
        for (int i = 0; i < base.size(); i++) {
            identity[i][i] = 1;
        }
        return identity;
    }

    vvll t = pow_mod(base, exp / 2);
    if (exp % 2 == 0) {
        return multiply_matrices(t, t);
    } else {
        return multiply_matrices(t, multiply_matrices(t, base));
    }

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll k; cin >> k;

    // f(0) = 4
    // f(1) = 9
    // f(2) = 5
    // f(n) = 4 f(n-3) + 9 f(n-2) + 5 f(n-1)

    if (k == 0) {
        cout << 4 << endl;
        return 0;
    }
    if (k == 1) {
        cout << 9 << endl;
        return 0;
    }
    if (k == 2) {
        cout << 5 << endl;
        return 0;
    }

    vvll pow_matrix = {{5, 9, 4}, {1, 0, 0}, {0, 1, 0}};
    vvll base_matrix = {{5, 0, 0}, {9, 0, 0}, {4, 0, 0}};
    vvll ans = pow_mod(pow_matrix, k - 2);

    ans = multiply_matrices(ans, base_matrix);
    cout << ans[0][0] << endl;

}

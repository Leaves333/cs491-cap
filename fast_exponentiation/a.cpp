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

const ll MOD = 1000000007;

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
    
    if (k == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (k == 1) {
        cout << 1 << endl;
        return 0;
    }

    vvll pow_matrix = {{1, 1}, {1, 0}};
    vvll base_matrix = {{1, 0}, {0, 0}};
    vvll ans = pow_mod(pow_matrix, k - 1);

    ans = multiply_matrices(ans, base_matrix);
    cout << ans[0][0] << endl;
}

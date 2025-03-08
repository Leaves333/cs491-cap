#include <chrono>
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

    ll n;
    cin >> n;
    auto start = chrono::high_resolution_clock::now();

    vll base_values = {
        1,         1,         1,         1,         1,         2,
        3,         4,         5,         6,         9,         13,
        18,        24,        31,        42,        58,        80,
        109,       146,       197,       268,       366,       499,
        676,       916,       1243,      1690,      2299,      3122,
        4237,      5751,      7811,      10614,     14418,     19580,
        26587,     36106,     49043,     66614,     90473,     122869,
        166866,    226632,    307810,    418060,    567784,    771122,
        1047296,   1422396,   1931846,   2623743,   3563422,   4839650,
        6572979,   8927124,   12124405,  16466764,  22364329,  30374128,
        41252687,  56027435,  76093745,  103346791, 140360543, 190630869,
        258905636, 351633091, 477570952, 648613579, 880915392, 198172162,
        626670486, 210391671, 2544512,   77779182,  537481966, 521106302,
        215666521, 873400713, 842782295, 592322226, 758329236, 208518018,
        116607436, 80196827,  267810688, 625131724, 154467744, 286658697,
        402114808, 523031874, 261804085, 104343078, 158286247, 523686981,
        515025136, 32913847,  503163636, 952075488,
    }; // precompute f(0) to f(99)
    reverse(base_values.begin(), base_values.end());

    // initialize the base matrix with precomputed values
    vvll base_matrix(100, vll(100));
    for (int i = 0; i < 100; i++) {
        base_matrix[i][0] = base_values[i];
    }

    // defining the recurrence relation
    vvll pow_matrix(100, vll(100));
    for (int i = 0; i < 99; i++) {
        pow_matrix[i + 1][i] = 1;
    }
    pow_matrix[0][0] = 1;
    pow_matrix[0][4] = 1;
    pow_matrix[0][9] = 1;
    pow_matrix[0][24] = 1;
    pow_matrix[0][49] = 1;
    pow_matrix[0][99] = 1;

    vvll ans = pow_mod(pow_matrix, n - 1);
    ans = pow_mod(ans, 100);
    ans = multiply_matrices(ans, pow_matrix);
    ans = multiply_matrices(ans, base_matrix);
    cout << ans[0][0] << endl;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds  >(end - start);
    cout << duration.count() << "ms" << endl;

    // cur time: 2760ms
}

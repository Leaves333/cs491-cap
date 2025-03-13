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
struct matrix {
    ll arr[100][100];
};

matrix multiply_matrices(const matrix &first, const matrix &second) {
    matrix res;
    memset(res.arr, 0, sizeof(res.arr));
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ll sum = 0;
            for (int k = 0; k < 100; k++) {
                sum += first.arr[i][k] * second.arr[k][j];
                sum %= MOD;
            }
            res.arr[i][j] = sum;
        }
    }
    return res;
}

matrix pow_mod(matrix base, ll exp) {

    matrix res;
    memset(res.arr, 0, sizeof(res.arr));
    for (int i = 0; i < 100; i++) {
        res.arr[i][i] = 1;
    }

    while (exp > 0) {
        if (exp & 1) {
            res = multiply_matrices(res, base);
        }
        base = multiply_matrices(base, base);
        exp >>= 1;
    }

    return res;

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;

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

    // initialize the base matrix with precomputed values
    matrix base_matrix;
    memset(base_matrix.arr, 0, sizeof(base_matrix.arr));
    for (int i = 0; i < 100; i++) {
        base_matrix.arr[i][0] = base_values[99 - i];
    }

    // defining the recurrence relation
    matrix pow_matrix;
    memset(pow_matrix.arr, 0, sizeof(pow_matrix.arr));
    for (int i = 0; i < 99; i++) {
        pow_matrix.arr[i + 1][i] = 1;
    }
    pow_matrix.arr[0][0] = 1;
    pow_matrix.arr[0][4] = 1;
    pow_matrix.arr[0][9] = 1;
    pow_matrix.arr[0][24] = 1;
    pow_matrix.arr[0][49] = 1;
    pow_matrix.arr[0][99] = 1;

    matrix ans = pow_mod(pow_matrix, n - 1);
    ans = pow_mod(ans, 100);
    ans = multiply_matrices(ans, pow_matrix);
    ans = multiply_matrices(ans, base_matrix);
    cout << ans.arr[0][0] << endl;

    // cur time: 1150ms
    
}

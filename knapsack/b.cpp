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

struct upgrade {
    int cost, power;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, x, y, z;
    cin >> n >> x >> y >> z;
    vector<upgrade> strength(x), precision(y), luck(z);
    for (int i = 0; i < x; i++) {
        int c, v;
        cin >> c >> v;
        strength[i] = {c, v};
    }
    for (int i = 0; i < y; i++) {
        int c, v;
        cin >> c >> v;
        precision[i] = {c, v};
    }
    for (int i = 0; i < z; i++) {
        int c, v;
        cin >> c >> v;
        luck[i] = {c, v};
    }

    // dp[i][j] stores max value when only first i items are considered
    // with capacity j
    vvll dp_strength(x + 1, vll(n + 1));
    vvll dp_precision(y + 1, vll(n + 1));
    vvll dp_luck(z + 1, vll(n + 1));

    for (int i = 1; i <= x; i++) {
        for (int j = 0; j <= n; j++) {
            dp_strength[i][j] = dp_strength[i-1][j];
            upgrade cur = strength[i - 1];
            if (j - cur.cost >= 0) {
                dp_strength[i][j]= max(dp_strength[i][j], dp_strength[i-1][j-cur.cost] + cur.power);
            }
        }
    }
    for (int i = 1; i <= y; i++) {
        for (int j = 0; j <= n; j++) {
            dp_precision[i][j] = dp_precision[i-1][j];
            upgrade cur = precision[i - 1];
            if (j - cur.cost >= 0) {
                dp_precision[i][j]= max(dp_precision[i][j], dp_precision[i-1][j-cur.cost] + cur.power);
            }
        }
    }
    for (int i = 1; i <= z; i++) {
        for (int j = 0; j <= n; j++) {
            dp_luck[i][j] = dp_luck[i-1][j];
            upgrade cur = luck[i - 1];
            if (j - cur.cost >= 0) {
                dp_luck[i][j]= max(dp_luck[i][j], dp_luck[i-1][j-cur.cost] + cur.power);
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            int k = n - i - j;
            if (k < 0)
                continue;
            ll cur = dp_strength[x][i] * dp_precision[y][j] * dp_luck[z][k];
            ans = max(ans, cur);
        }
    }
    cout << ans << endl;
    
}

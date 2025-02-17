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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    int d[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }

    int k; cin >> k;
    while (k--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;

        ll ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][a] + d[b][j] + c);
                d[i][j] = min(d[i][j], d[i][b] + d[a][j] + c);
                d[j][i] = min(d[j][i], d[j][a] + d[b][i] + c);
                d[j][i] = min(d[j][i], d[j][b] + d[a][i] + c);
                ans += d[i][j];
            }
        }
        cout << ans << " ";
    }
    cout << endl;
}

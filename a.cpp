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

    int n;
    cin >> n;
    ll d[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
            if (d[i][j] == 0)
                d[i][j] = LLONG_MAX;
            if (i == j)
                d[i][j] = 0;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (d[i][k] < LLONG_MAX && d[k][j] < LLONG_MAX)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][j] == LLONG_MAX) {
                cout << -1 << " ";
            } else {
                cout << d[i][j] << " ";
            }
        }
        cout << endl;
    }
    
}

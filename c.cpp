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
    queue<pii> edges_to_check;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
            if (d[i][j])
                edges_to_check.push(make_pair(i, j));
        }
    }

    while (!edges_to_check.empty()) {
        pii edge = edges_to_check.front();
        edges_to_check.pop();
        for (int i = 0; i < n; i++) {
            if (d[edge.second][i] && !d[edge.first][i]) {
                d[edge.first][i] = 1;
                edges_to_check.push(make_pair(edge.first, i));
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
}

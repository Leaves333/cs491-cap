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

void dfs(int x, vvi &edges, vector<bool> &visited) {
    if (visited[x])
        return;
    visited[x] = true;
    for (int dest : edges[x]) {
        dfs(dest, edges, visited);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vvi edges(n);
    vvi d(n, vi(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
            if (d[i][j])
                edges[i].push_back(j);
        }
    }

    for (int i = 0; i < n; i++) {
        vector<bool> visited(n);
        dfs(i, edges, visited);
        for (int j = 0; j < n; j++) {
            if (visited[j])
                d[i][j] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
}

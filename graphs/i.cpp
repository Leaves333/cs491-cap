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

map<int, vi> edges;
vi color;

void dfs(int x, int c, const int k) {
    c %= k;
    color[x] = c + 1;
    for (auto child : edges[x]) {
        if (color[child] == -1) {
            dfs(child, c + 1, k);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;
    color = vi(n+1, -1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            dfs(i, 0, k);
        }
    }

    if (k == 1 && m > 0) {
        cout << -1 << endl;
    } else {
        for (int i = 1; i <= n; i++) {
            cout << color[i] << endl;
        }
    }

}

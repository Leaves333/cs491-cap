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

vector<string> grid;
set<pii> visited;

void dfs(int x, int y) {
    if (visited.count(make_pair(x, y)) || grid[x][y] == 'O')
        return;
    visited.insert(make_pair(x, y));
    int changes[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (auto c : changes) {
        int new_x = x + c[0];
        int new_y = y + c[1];
        if (new_x < 0 || new_x >= grid.size() || new_y < 0 || new_y >= grid[0].size())
            continue;
        dfs(new_x, new_y);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        grid.push_back(s);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited.count(make_pair(i, j)) && grid[i][j] == 'L') {
                ans++;
                dfs(i, j);
            }
        }
    }
    cout << max(0, ans - 1) << endl;
}

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    
    vvi grid(n, vi(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    vvi dp(n, vi(m, 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            queue<pair<int, pii>> pq;
            pq.push({dp[i][j], {i, j}});
            while (!pq.empty()) {
                auto top = pq.front().second;
                int x = top.first;
                int y = top.second;
                pq.pop();

                int new_dist = dp[x][y] + 1;
                int changes[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
                for (auto c : changes) {
                    int new_x = x + c[0];
                    int new_y = y + c[1];
                    if (new_x < 0 || new_y < 0 || new_x >= n || new_y >= m)
                        continue;
                    if (dp[new_x][new_y] >= new_dist)
                        continue;
                    if (grid[new_x][new_y] <= grid[x][y])
                        continue;
                    dp[new_x][new_y] = new_dist;
                    pq.push({new_dist, {new_x, new_y}});
                }
            }
        }
    }

    int ans = 0;
    for (auto row : dp)
        for (auto x : row)
            ans = max(ans, x);
    cout << ans << endl;
}

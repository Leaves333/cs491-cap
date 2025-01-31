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

void search(int pos, int max, vector<vector<bool>> &grid, int remaining_kings, int &count) {

    if (remaining_kings == 0) {
        count++;
        return;
    }

    for (int k = pos; k < max; k++) {
        int i = k / grid[0].size();
        int j = k % grid[0].size();

        bool can_place = true;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (i + x < 0 || i + x >= grid.size() || j + y < 0 || j + y >= grid[0].size())
                    continue;
                if (grid[i + x][j + y]) 
                    can_place = false;
            }
        }
        if (!can_place)
            continue;

        grid[i][j] = true;
        search(k + 1, max, grid, remaining_kings - 1, count);
        grid[i][j] = false;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<bool>> grid(n, vector<bool>(m, false));
    int ans = 0;
    int max = n * m;
    search(0, max, grid, k, ans);
    cout << ans << endl;
}

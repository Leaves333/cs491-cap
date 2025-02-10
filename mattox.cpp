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

const int RECURSION_DEPTH = 30;
int n, m;
int dist[20][20][20][20][2];

int search(int mx, int my, int px, int py, bool player_move, int depth) {

    // base case 1:
    // mattox and player at same position
    if (mx == px && my == py) {
        if (player_move) {
            return INT_MIN; // mattox wins
        } else {
            return 0; // i win
        }
    }

    // base case 2:
    // recursion depth exceeded
    if (depth > RECURSION_DEPTH) {
        return INT_MIN;
    }

    // base case 3:
    // we've seen this state before
    if (dist[mx][my][px][py][player_move] != -1) {
        return dist[mx][my][px][py][player_move];
    }

    int time_to_win = 0;
    if (player_move) {
        int player_changes[8][2] = {{0, 1}, {0, 2}, {0, -1}, {0, -2},
                                    {1, 0}, {2, 0}, {-1, 0}, {-2, 0}};
        for (auto c : player_changes) {
            int new_x = px + c[0];
            int new_y = py + c[1];
            if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m)
                continue; // out of bounds
            int search_result = search(mx, my, new_x, new_y, !player_move, depth+1);
            if (search_result == INT_MIN)
                continue; // win not found
            time_to_win = min(time_to_win, search_result);
        }
    } else {
        int mattox_changes[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto c : mattox_changes) {
            int new_x = mx + c[0];
            int new_y = my + c[1];
            if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m)
                continue; // out of bounds
            int search_result = search(new_x, new_y, px, py, !player_move, depth+1);
            if (search_result == INT_MIN)
                continue; // win not found
            time_to_win = max(time_to_win, search_result);
        }
    }

    dist[mx][my][px][py][player_move] = time_to_win + 1;
    return dist[mx][my][px][py][player_move];

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            for (int x = 0; x < 20; x++) {
                for (int y = 0; y < 20; y++) {
                    dist[i][j][x][y][false] = -1;
                    dist[i][j][x][y][true] = -1;
                }
            }
        }
    }

    cout << search(0, 0, n-1, m-1, false, 0) << endl;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    cout << i << " " << j << " " << x << " " << y << ": ";
                    cout << dist[i][j][x][y][false] << " ";
                    cout << dist[i][j][x][y][true] << endl;
                }
            }
        }
    }

}

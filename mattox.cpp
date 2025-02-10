#include <algorithm>
#include <climits>
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

int n, m;

// mx, my, px, py, player_move;
// for each state, how many moves am i away from winnning?
ll dist[20][20][20][20][2];

// returns the number of moves until win
ll search(int mattox_x, int mattox_y, int player_x, int player_y, bool player_move, int moves) {

    cout << "search called with " << mattox_x << " " << mattox_y << " "
        << player_x << " " << player_y << " " << player_move << " " << moves << endl;

    if (moves > 10) {
        return -1;
    }

    if (mattox_x == player_x && mattox_y == player_y) {
        /*dist[mattox_x][mattox_y][player_x][player_y][player_move] = 0;*/
        if (player_move)
            return -1;
        else
            return moves;
    }

    if (dist[mattox_x][mattox_y][player_x][player_y][player_move] != -490) {
        return dist[mattox_x][mattox_y][player_x][player_y][player_move];
    }

    int moves_to_here = 0;
    if (player_move) {
        int player_changes[8][2] = {{1, 0}, {2, 0}, {-1, 0}, {-2, 0},
                                    {0, 1}, {0, 2}, {0, -1}, {0, -2}};
        for (auto c : player_changes) {
            int new_x = player_x + c[0];
            int new_y = player_y + c[1];
            if (new_x < 0 || new_y < 0 || new_x >= n || new_y >= m)
                continue;
            int res = search(mattox_x, mattox_y, new_x, new_y, !player_move, moves + 1);
            if (res != -1)
                moves_to_here = min(moves_to_here, res);
        }
    } else {
        int mattox_changes[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (auto c : mattox_changes) {
            int new_x = mattox_x + c[0];
            int new_y = mattox_y + c[1];
            if (new_x < 0 || new_y < 0 || new_x >= n || new_y >= m)
                continue;
            int res = search(new_x, new_y, player_x, player_y, !player_move, moves + 1);
            if (res != -1)
                moves_to_here = max(moves_to_here, res);
        }
    }

    return moves_to_here;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    // magic number
                    dist[i][j][x][y][0] = -490;
                    dist[i][j][x][y][1] = -490;
                }
            }
        }
    }

    cout << search(0, 0, n-1, m-1, false, 0) << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    cout << i << " " << j << " " << x << " " << y;
                    cout << ": ";
                    cout << dist[i][j][x][y][0] << " ";
                    cout << dist[i][j][x][y][1] << endl;
                }
            }
        }
    }

}

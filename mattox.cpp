#include <climits>
#include <cstring>
#include <iostream>
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

    ll dist[n][m][n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    dist[i][j][x][y] = LLONG_MAX;
                }
            }
        }
    }

    ll ans = LLONG_MIN;

    priority_queue<pair<ll, array<int, 4>>> pq;
    pq.push(make_pair(0, array<int, 4>{0, 0, n-1, m-1}));

    while (!pq.empty()) {

        ll time = pq.top().first * -1;
        auto arr = pq.top().second; // mattox x.y, player x.y
        pq.pop();

        int mattox_x = arr[0];
        int mattox_y = arr[1];
        int player_x = arr[2];
        int player_y = arr[3];

        dist[mattox_x][mattox_y][player_x][player_y] = time;

        /*cout << "time: " << time;*/
        /*cout << "\tmattox: " << mattox_x << ", " << mattox_y;*/
        /*cout << "\tplayer: " << player_x << ", " << player_y;*/
        /*cout << endl;*/

        if (player_x == mattox_x && player_y == mattox_y) {
            ans = max(ans, time);
            continue;
        }

        int player_changes[8][2] = {{1, 0}, {2, 0}, {-1, 0}, {-2, 0},
                                    {0, 1}, {0, 2}, {0, -1}, {0, -2}};
        int mattox_changes[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for (auto cp : player_changes) {
            for (auto cm : mattox_changes) {
                int new_player_x = player_x + cp[0];
                int new_player_y = player_y + cp[1];
                int new_mattox_x = mattox_x + cm[0];
                int new_mattox_y = mattox_y + cm[1];
                if (new_player_x >= n || new_player_y >= m || new_mattox_x >= n || new_mattox_y >= m)
                    continue;
                if (new_player_x < 0 || new_player_y < 0 || new_mattox_x < 0 || new_mattox_y < 0)
                    continue;
                if (dist[new_mattox_x][new_mattox_y][new_player_x][new_player_y] <= time + 1)
                    continue;
                pq.push(make_pair((time + 1) * -1,
                    array<int, 4>{new_mattox_x, new_mattox_y, new_player_x, new_player_y}));
            }
        }

    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << i << " " << j << ":\t";
            cout << dist[i][j][i][j] << endl;
        }
    }


    if (ans == LLONG_MIN) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

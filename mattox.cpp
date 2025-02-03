#include <array>
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

struct pos {
    int x = 0;
    int y = 0;

    bool operator==(const pos &other) {
        return x == other.x && y == other.y;
    }
};

bool operator<(const pos& first, const pos& second) {
    return first.x < second.x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    map<array<int, 4>, ll> dist;
    ll ans = LLONG_MIN;

    priority_queue<pair<ll, array<int, 4>>> pq;
    pq.push(make_pair(0, array<int, 4>{n, m, 1, 1}));

    while (!pq.empty()) {

        ll time = pq.top().first * -1;
        auto arr = pq.top().second;
        pos player{arr[0], arr[1]};
        pos mattox{arr[2], arr[3]};
        pq.pop();

        dist[make_pair(player, mattox)] = time;

        cout << "time: " << time;
        cout << " player: " << player.x << ", " << player.y;
        cout << "\tmattox: " << mattox.x << ", " << mattox.y;
        cout << endl;

        if (player == mattox) {
            ans = max(ans, time);
            continue;
        }

        int player_changes[8][2] = {{1, 0}, {2, 0}, {-1, 0}, {-2, 0},
                                    {0, 1}, {0, 2}, {0, -1}, {0, -2}};
        int mattox_changes[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for (auto cp : player_changes) {
            for (auto cm : mattox_changes) {
                pos new_player = player;
                pos new_mattox = mattox;
                new_player.x += cp[0];
                new_player.y += cp[1];
                new_mattox.x += cm[0];
                new_mattox.y += cm[1];
                if (new_player.x > n || player.y > m || new_mattox.x > n || mattox.y > m)
                    continue;
                if (new_player.x < 1 || player.y < 1 || new_mattox.x < 1 || mattox.x < 1)
                    continue;
                if (dist[make_pair(new_player, new_mattox)] >= time + 1)
                    continue;
                pq.push(make_pair((time + 1) * -1, array<int, 4>{}));
            }
        }

    }

    if (ans == LLONG_MIN) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

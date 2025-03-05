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

struct edge {
    int dest;
    bool color;
};

vector<vector<edge>> edges_true;
vector<vector<edge>> edges_false;

vector<vector<bool>> visited(2);
int starting_loc;
bool starting_color;

bool dfs(int location, bool color) {
    if (location == starting_loc && color != starting_color)
        return false;
    if (visited[color][location])
        return true;

    visited[color][location] = true;
    bool status = true;
    const vector<edge>& edges = (color ? edges_true[location] : edges_false[location]);
    for (edge e : edges) {
        status &= dfs(e.dest, e.color);
    }

    return status;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    edges_true.assign(n + 1, {});
    edges_false.assign(n + 1, {});
    while (m--) {
        int p, q;
        string v1, v2;
        string trash_s;
        char trash_c;

        cin >> trash_c >> p >> trash_s >> v1;
        cin >> trash_s >> trash_c >> q >> trash_s >> v2;

        bool b1 = (v1 == "true");
        bool b2 = (v2 == "true");

        if (b1) {
            edges_true[p].push_back(edge{q, b2});
        } else {
            edges_false[p].push_back(edge{q, b2});
        }
    }

    visited[false].assign(n + 1, false);
    visited[true].assign(n + 1, false);
    bool good = true;

    for (int i = 1; i <= n; i++) {
        starting_loc = i;
        bool ok = false;
        if (!visited[false][i]) {
            starting_color = false;
            ok |= dfs(i, false);
        }
        if (!visited[true][i]) {
            starting_color = true;
            ok |= dfs(i, true);
        }
        if (!ok)
            good = false;
    }

    if (good) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

}

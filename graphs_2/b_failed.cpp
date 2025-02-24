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
vector<vector<bool>> can_color(2);
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

    can_color[color][location] = status;
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
    can_color[false].assign(n + 1, false);
    can_color[true].assign(n + 1, false);

    for (int i = 1; i <= n; i++) {
        starting_loc = i;
        if (!visited[false][i]) {
            starting_color = false;
            dfs(i, false);
        }
        if (!visited[true][i]) {
            starting_color = true;
            dfs(i, true);
        }
    }

    bool good = true;
    for (int i = 1; i <= n; i++) {
        if (!can_color[false][i] && !can_color[true][i]) {
            good = false;
        }

        /*cout << "i=" << i << ", ";*/
        /*cout << "can color true: " << can_color[true][i] << ", ";*/
        /*cout << "can color false: " << can_color[false][i] << endl;*/
    }

    if (good) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

}

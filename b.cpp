#include <bits/stdc++.h>
#include <vector>
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

bool dfs() {
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<edge>> edges_true(n + 1);
    vector<vector<edge>> edges_false(n + 1);
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

    vector<vector<bool>> visited(2, vector<bool>(n+1));
    for (int i = 1; i <= n; i++) {
        if (!visited[false][i]) {
        }
        if (!visited[true][i]) {
        }
    }

}

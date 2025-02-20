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
    int dest, x;
};

vi color;
vector<vector<edge>> edges;

bool dfs(int x, int c) {

    if (color[x] != -1) {
        if (color[x] != c)
            return false;
        return true;
    }
    
    bool ret = true;
    color[x] = c;
    for (edge e : edges[x]) {
        ret &= dfs(e.dest, c ^ e.x);
    }

    return ret;

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    edges.assign(n + 1, {});
    while (m--) {
        char trash_char;
        string trash_string;
        int a, b, k;
        
        cin >> trash_char >> a >> trash_string >> trash_char >> b >> trash_string >> k;
        edges[a].push_back(edge{b, k});
        edges[b].push_back(edge{a, k});
    }

    color.assign(n + 1, -1);
    bool good = true;
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            good &= dfs(i, 0);
        }
    }

    if (good) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

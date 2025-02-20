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

// we're finding cut points today !!!

vvi edges;

vector<bool> visited;
vi tin, low;
int timer;

set<int> cut_points;

void dfs(int v, int parent = -1) {
    /*cout << "dfs at " << v << endl;*/
    visited[v] = true;
    low[v] = timer;
    tin[v] = low[v];
    timer++;

    int children = 0;
    for (int to : edges[v]) {
        if (to == parent)
            continue;
        if (visited[to]) {
            // this is a back edge !!
            low[v] = min(low[v], tin[to]);
        } else {
            // this is a tree edge !!
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && parent != -1)
                cut_points.insert(v);
            children++;
        }
    }

    if (parent == -1 && children > 1) {
        cut_points.insert(v);
    }
}

void find_cutpoints() {
    /*cout << "find cutpoints called !!!" << endl;*/
    int n = edges.size();
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    edges.assign(n + 1, {});

    while (m--) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    find_cutpoints();

    cout << cut_points.size() << endl;
    for (auto x : cut_points) {
        cout << x << " ";
    }
    cout << endl;

}

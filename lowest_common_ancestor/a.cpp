#include <vector>
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

struct edge {
    int dest, cost;
};

int n, l; // n is number of nodes, l is log_2 n
vector<vector<edge>> adj; // adjacency list of numbers
vll cost; // cost to get to each node from root

int timer;
vi tin, tout;
vvi up;

void dfs(int v, int p, ll depth)
{
    cost[v] = depth;
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (edge e : adj[v]) {
        int u = e.dest;
        if (u != p)
            dfs(u, v, depth + e.cost);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m;
    cin >> n >> m;
    adj.assign(n + 1, {});

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(edge{v, w});
        adj[v].push_back(edge{u, w});
    }

    n++; // our edges are 1 indexed
    int root = 1;

    // do some preprocessing
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    cost.assign(n, 0);
    dfs(root, root, 0);

    vi nums(m);
    for (int i = 0; i < m; i++) {
        cin >> nums[i];
    }
    nums.push_back(1);

    ll ans = 0;
    int cur_location = 1;
    for (int i = 0; i < m + 1; i++) {
        int prev = lca(cur_location, nums[i]);
        ans += cost[cur_location] - cost[prev];
        ans += cost[nums[i]] - cost[prev];
        cur_location = nums[i];
    }

    cout << ans << endl;

}

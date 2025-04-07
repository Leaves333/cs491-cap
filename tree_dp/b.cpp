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

vector<bool> visited;

// dfs starting at vertex v
// appends v to output vector after dfs leaves it
void dfs(int v, const vvi &edges, vi &output) {
    visited[v] = true;
    for (int dest : edges[v])
        if (!visited[dest])
            dfs(dest, edges, output);
    output.push_back(v);
}

// input: edges: adj list of G
// output: components: ssc of G
// output: condensed_edges: adjacency list of G^SCC (by root vertices) ??? what does this mean
// output: roots: root vertex of each v
void strongly_connected_components(const vvi &edges, vvi &components, vvi &condensed_edges, vi &roots) {

    // init some variables
    int n = edges.size();
    components.clear();
    condensed_edges.clear();

    // first dfs:
    // fill order with a sorted list of vertices
    vi order;
    visited.assign(n, false);
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i, edges, order);

    // create adjacency list of G transposed
    vvi edges_tranposed(n);
    for (int v = 0; v < n; v++)
        for (int u : edges[v])
            edges_tranposed[u].push_back(v);

    reverse(order.begin(), order.end());
    visited.assign(n, false);
    roots.assign(n, 0); // roots[v] stores root vertex of v's SCC

    // second dfs:
    // dfs through edges_transposed
    // find all the connected components
    for (int v : order) {
        if (!visited[v]) {
            vi component;
            dfs(v, edges_tranposed, component);
            components.push_back(component);
            int root = *min_element(component.begin(), component.end());
            for (auto u : component) {
                roots[u] = root;
            }
        }
    }

    // add edges to condensed graph
    // for each edge in the original graph, if they aren't part of the same scc
    // add a new edge to the condensed graph
    condensed_edges.assign(n, {});
    for (int v = 0; v < n; v++)
        for (auto u : edges[v])
            if (roots[v] != roots[u])
                condensed_edges[roots[v]].push_back(roots[u]);
}

// generates a postorder traversal of the dag
void postorder(int x, const vvi &condensed_edges, vi &ordering, vector<bool> &seen) {
    if (seen[x])
        return;
    seen[x] = true;
    for (auto dest : condensed_edges[x]) {
        postorder(dest, condensed_edges, ordering, seen);
    }
    ordering.push_back(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vi diamonds(n);
        for (int i = 0; i < n; i++) {
            cin >> diamonds[i];
        }
        vvi edges(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            edges[x].push_back(y);
        }

        vvi components;
        vvi condensed_edges;
        vi roots;
        strongly_connected_components(edges, components, condensed_edges, roots);

        vi values(n);
        set<int> valid_roots;
        for (vi comp : components) {
            valid_roots.insert(roots[comp[0]]);
            if (comp.size() <= 1) {
                values[roots[comp[0]]] += min(diamonds[comp[0]], 3);
            } else {
                for (int x : comp) {
                    values[roots[x]] += diamonds[x];
                }
            }
        }

        vector<bool> seen(n, false);
        vi ordering;
        for (auto x : valid_roots) {
            if (!seen[x])
                postorder(x, condensed_edges, ordering, seen);
        }

        int ans = 0;
        vi dp(n);
        for (auto x : ordering) {
            int best_child = 0;
            for (auto dest : condensed_edges[x]) {
                best_child = max(best_child, dp[dest]);
            }
            dp[x] = values[x] + best_child;
            ans = max(ans, dp[x]);
        }
        cout << ans << endl;

    }
}

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    n++;

    vvi edges(n * 2);
    while (m--) {
        int p, q;
        string v1, v2;
        string trash_s;
        char trash_c;

        cin >> trash_c >> p >> trash_s >> v1;
        cin >> trash_s >> trash_c >> q >> trash_s >> v2;

        bool b1 = (v1 == "true");
        bool b2 = (v2 == "true");
        edges[2 * p + b1].push_back(2 * q + b2);
    }

    cout << "here's the edges: " << endl;
    for (int i = 0; i < edges.size(); i++) {
        cout << i << " : ";
        for (auto x : edges[i]) {
            cout << x << " ";
        }
        cout << endl;
    }

    vvi components, condensed_edges;
    vi roots;
    strongly_connected_components(edges, components, condensed_edges, roots);

    for (int i = 1; i < n; i++) {
        cout << i << " true is in " << roots[2 * i] << endl;
        cout << i << " false is in " << roots[2 * i + 1] << endl;
    }

    cout << "components are: " << endl;
    for (auto c : components) {
        for (auto x : c)
            cout << x << " ";
        cout << endl;
    }

    cout << "here's roots: " << endl;
    for (int i = 0; i < roots.size(); i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < roots.size(); i++) {
        cout << roots[i] << " ";
    }
    cout << endl;

    for (int i = 1; i < n; i++) {
        if (roots[2 * i] == roots[2 * i + 1]) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;

}

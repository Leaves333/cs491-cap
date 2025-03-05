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
vector<bool> good;

// returns if there is a contradiction if cur is in the graph
bool dfs(int cur, vvi &edges, set<int> &seen) {

    // base case
    if (visited[cur])
        return good[cur];
    visited[cur] = true;
    good[cur] = true;

    cout << "dfs with cur=" << cur << ", ";
    cout << "seen=";
    for (auto x : seen)
        cout << x << ", ";
    cout << endl;

    // find the opposite node
    int counterpart = (cur / 2) * 2;
    if (counterpart == cur)
        counterpart++;

    // if its counterpart was previously in the stack, there is a contradiction
    // and cur cannot be a valid node
    if (seen.count(counterpart)) {
        cout << cur << " is bad... " << endl;
        good[cur] = false;
        return false;
    }

    // dfs to adjacent nodes
    bool result = true;
    seen.insert(cur);
    for (auto dest : edges[cur]) {
        cout << "going from " << cur << " to " << dest << "... " << endl;
        result &= dfs(dest, edges, seen);
    }
    seen.erase(cur);

    cout << cur << " is " << result << endl;
    good[cur] = result;
    return result;
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

    // the plan:
    // dfs through all the nodes
    // if a node can be assigned neither true nor false
    // then there is no answer
    //
    // good stores if there is a contradiction if we assume
    // the node is colored the parity of good[i]

    visited.assign(n * 2, false);
    good.assign(n * 2, false);

    /*for (int i = 2; i < 2 * n; i++) {*/
    /*    if (!visited[i]) {*/
    /*        set<int> seen;*/
    /*        dfs(i, edges, seen);*/
    /*    }*/
    /*}*/

    set<int> seen;
    dfs(3, edges, seen);
    dfs(4, edges, seen);
    dfs(5, edges, seen);
    dfs(6, edges, seen);
    dfs(7, edges, seen);
    dfs(2, edges, seen);

    cout << "here's good: " << endl;
    for (int i = 0; i < 2 * n; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < 2 * n; i++) {
        cout << good[i] << " ";
    }
    cout << endl;

    for (int i = 1; i < n; i++) {
        if (!good[2 * i] && !good[2 * i + 1]) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;

}

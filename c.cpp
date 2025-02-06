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

const int NUM_VERTICES = 1001;
vi values(NUM_VERTICES);
vi parent(NUM_VERTICES);
vvi children(NUM_VERTICES);

int dfs(int root, bool find_min) {
    int ret = values[root];
    for (auto child : children[root]) {
        if (find_min)
            ret = min(ret, values[child]);
        else
            ret = max(ret, values[child]);
        dfs(child, find_min);
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> values[i];
    }

    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        parent[i] = p;
        children[p].push_back(i);
    }

    while (m--) {

        char op;
        int v, k;
        cin >> op >> v >> k;

        int extreme = dfs(v, (op == '-'));
        int p = parent[v];
        int parent_value = values[p];
        while (true) {
            if (p == 0) {
                parent_value = -1;
                break;
            } else if (op == '-' && parent_value > values[v]) {
                p = parent[p];
                parent_value = values[p];
            } else if (op == '+' && parent_value < values[v]) {
                p = parent[p];
                parent_value = values[p];
            } else {
                break;
            }
        }

        /*cout << "dfs on vertex " << v << "->" << values[v] << ", extreme=" << extreme << endl;*/
        /*cout << "parent value = " << parent_value << endl;*/
        /**/
        if (parent_value == -1) {
            cout << "YES" << endl;
        } else if (op == '-' && values[v] > parent_value && extreme - k < parent_value) {
            cout << "NO" << endl;
        } else if (op == '+' && values[v] < parent_value && extreme + k > parent_value) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }

        /*cout << endl;*/
    }
}

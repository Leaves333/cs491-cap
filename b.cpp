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

bool dfs(int x, map<int, vi> &edges, vi &topsort, vector<bool> &visited, set<int> &cur_stack) {
    if (cur_stack.count(x))
        return false;
    if (visited[x])
        return true;
    visited[x] = true;
    cur_stack.insert(x);
    bool res = true;
    for (auto dest : edges[x]) {
        res &= dfs(dest, edges, topsort, visited, cur_stack);
    }
    cur_stack.erase(cur_stack.find(x));
    topsort.push_back(x);
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    map<int, vi> edges;
    while (m--) {
        int k;
        cin >> k;
        k--;
        int last;
        cin >> last;
        while (k--) {
            int cur;
            cin >> cur;
            edges[last].push_back(cur);
            last = cur;
        }
    }

    vi topsort;
    vector<bool> visited(3*n + 1, false);
    bool res = true;
    for (int i = 1; i <= 3*n; i++) {
        if (!visited[i]) {
            set<int> cur_stack;
            cur_stack.clear();
            res &= dfs(i, edges, topsort, visited, cur_stack);
        }
    }
    reverse(topsort.begin(), topsort.end());

    if (!res) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for (int i = 0; i < topsort.size(); i++) {
            cout << topsort[i] << " ";
            if (i % 3 == 2) {
                cout << endl;
            }
        }
    }
}

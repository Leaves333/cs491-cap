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
    int dest, weight;
};

map<int, vector<edge>> edges;
set<int> visited;
vvi cycles;
vi cycle_weights;

void dfs(int x, set<int> &seen, vi &stack, vi &psum) {

    if (seen.count(x)) {
        auto find_it = find(stack.begin(), stack.end(), x);
        vi cycle(find_it, stack.end());
        cycle.push_back(x);
        cycles.push_back(cycle);
        cycle_weights.push_back(psum[psum.size()-1] - psum[distance(stack.begin(), find_it)]);
    }

    if (visited.count(x)) {
        return; // ???
    }

    visited.insert(x);
    seen.insert(x);
    stack.push_back(x);

    for (edge e : edges[x]) {
        psum.push_back(psum[psum.size()-1] + e.weight);
        dfs(e.dest, seen, stack, psum);
        psum.pop_back();
    }

    seen.erase(seen.find(x));
    stack.pop_back();

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    while (m--) {
        string first, second, throwaway;
        int b;
        cin >> first >> throwaway >> second >> throwaway >> b;
        int i = stoi(first.substr(1));
        int j = stoi(second.substr(1));

        edges[i].push_back(edge{j, b});
    }

    vi stack;
    vi psum;
    psum.push_back(0);

    for (int i = 1; i <= n; i++) {
        set<int> seen;
        if (!visited.count(i)) {
            dfs(i, seen, stack, psum);
        }
    }

    /*for (auto cycle : cycles) {*/
    /*    cout << "cycle found!! ";*/
    /*    for (auto x : cycle) {*/
    /*        cout << x << " -> ";*/
    /*    }*/
    /*    cout << endl;*/
    /*}*/
    /**/

    /*cout << "cycle weight!!!" << endl;*/
    /*for (auto x : cycle_weights) {*/
    /*    cout << x << endl;*/
    /*}*/

    for (auto x : cycle_weights) {
        if (x < 0) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
}

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<edge>> edges(n+1);
    while (m--) {
        int u, v, d;
        cin >> u >> v >> d;
        edges[u].push_back({v, d});
        edges[v].push_back({u, d});
    }
}

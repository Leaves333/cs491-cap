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
    int a, b, weight;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<edge> edges;
    while (m--) {
        string first, second, throwaway;
        int b;
        cin >> first >> throwaway >> second >> throwaway >> b;
        int i = stoi(first.substr(1));
        int j = stoi(second.substr(1));

        edges.push_back(edge{i, j, b});
    }

    // add an extra point that we can start the bellman-ford at
    for (int i = 1; i <= n; i++) {
        edges.push_back(edge{0, i, 0});
    }

    // do initial bellman-ford
    vector<ll> dist(n + 1, LLONG_MAX);
    dist[0] = 0;
    for (int i = 0; i < n + 1; i++) {
        for (edge e : edges) {
            if (dist[e.a] < LLONG_MAX) {
                dist[e.b] = min(dist[e.b], dist[e.a] + e.weight);
            }
        }
    }

    // check if any more relaxations
    bool relaxed = false;
    for (edge e : edges) {
        if (dist[e.a] < LLONG_MAX) {
            if (dist[e.a] + e.weight < dist[e.b])
                relaxed = true;
        }
    }

    if (relaxed) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }

}

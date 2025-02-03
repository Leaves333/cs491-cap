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

struct DSU {
    vi parent = vi(1000000);

    void make_set(int v) {
        parent[v] = v;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, m, k;
    cin >> n >> m >> k;

    ll a, b;
    cin >> a >> b;

    DSU dsu;
    vi entries(n);
    for (int i = 0; i < n; i++) {
        dsu.make_set(i);
    }

    while (k--) {
        ll x; cin >> x;
        int target = ((a * x) + b) % n;
        target = dsu.find_set(target);
        cout << target << endl;

        entries[target]++;
        if (entries[target] >= m) {
            dsu.union_sets((target+1)%n, target);
        }
    }
}

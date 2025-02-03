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
    vi parent = vi(100000);
    vi size = vi(100000);

    void make_set(int v) {
        parent[v] = v;
        size[v] = 1;
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
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q, l;
    cin >> n >> q >> l;

    DSU dsu;
    vll lengths(n);
    for (int i = 0; i < n; i++) {
        cin >> lengths[i];
        dsu.make_set(i);
        if (i > 0 && lengths[i-1] > l) {
            dsu.union_sets(i, i-1);
        }
    }

    set<int> tall_parents;
    for (int i = 0; i < n; i++) {
        if (lengths[i] > l) {
            tall_parents.insert(dsu.find_set(i));
        }
    }

    while (q--) {

        int c;
        cin >> c;

        if (c == 1) {
            int k, h;
            cin >> k >> h;
            k--;
            lengths[k] += h;

            if (lengths[k] > l) {
                vi before;
                before.push_back(dsu.find_set(k));
                if (k > 0 && lengths[k-1] > l) {
                    before.push_back(dsu.find_set(k-1));
                    dsu.union_sets(k, k-1);
                }
                if (k < n-1 && lengths[k+1] > l) {
                    before.push_back(dsu.find_set(k+1));
                    dsu.union_sets(k, k+1);
                }
                for (auto x : before) {
                    tall_parents.erase(x);
                }
                tall_parents.insert(dsu.find_set(k));
            }
        }

        else {
            cout << tall_parents.size() << endl;
        }

    }
}

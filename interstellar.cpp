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

    vi parent, size;

    void init_dsu(int n) {
        parent = vi(n);
        size = vi(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a == b)
            return;
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    int sqrt_n = 0;
    while (sqrt_n * sqrt_n < n) {
        sqrt_n++;
    }
    n++;

    DSU dsu;
    dsu.init_dsu(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        dsu.union_sets(u, v);
    }

    // find connected components
    map<int, vi> groups;
    for (int i = 1; i < n; i++) {
        int leader = dsu.find_set(i);
        groups[leader].push_back(i);
    }
    for (auto &[key, arr] : groups) {
        sort(arr.begin(), arr.end());
    }

    // do preprocessing
    // decomp[i][j] = sum of connected from i-th decomp to j-th planets
    vvll decomp(sqrt_n, vll(sqrt_n));
    for (int i = 0; i < sqrt_n; i++) {
        int l = i * sqrt_n;
        int r = (i + 1) * sqrt_n;

        vll arr(n);
        for (int j = 1; j < n; j++) {
            int leader = dsu.find_set(j);
            vi &arr = groups[leader];
            auto left = lower_bound(arr.begin(), arr.end(), l);
            auto right = upper_bound(arr.begin(), arr.end(), r);
            arr[j] = distance(left, right) - 1;
            decomp[j][i] += arr[j];
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        ll expected = 0;
        for (int i = l; i <= r; i++) {
            int leader = dsu.find_set(i);
            vi &arr = groups[leader];
            auto left = lower_bound(arr.begin(), arr.end(), l);
            auto right = upper_bound(arr.begin(), arr.end(), r);
            int planets = distance(left, right);
            /*cout << i << " can reach " << planets << " planets" << endl;*/
            expected += planets - 1;
        }
        cout << "expected " << expected << endl;

        int low = (l / sqrt_n) + !(l % sqrt_n == 0);
        int high = (r / sqrt_n);

        ll ans = 0;
        if (low <= high) {

            // TODO: handle sqrt decomp
            for (int i = low; i < high; i++) {
                // BUG: how do i actually handle this 
            }

            // handle stuff on left
            for (int i = l; i < low * sqrt_n; i++) {
                int leader = dsu.find_set(i);
                vi &arr = groups[leader];
                auto left = lower_bound(arr.begin(), arr.end(), l);
                auto right = upper_bound(arr.begin(), arr.end(), r);
                int planets = distance(left, right);
                ans += planets - 1;
            }

            // handle stuff on right
            for (int i = high * sqrt_n; i <= r; i++) {
                int leader = dsu.find_set(i);
                vi &arr = groups[leader];
                auto left = lower_bound(arr.begin(), arr.end(), l);
                auto right = upper_bound(arr.begin(), arr.end(), r);
                int planets = distance(left, right);
                ans += planets - 1;
            }

        } else {
            for (int i = l; i <= r; i++) {
                int leader = dsu.find_set(i);
                vi &arr = groups[leader];
                auto left = lower_bound(arr.begin(), arr.end(), l);
                auto right = upper_bound(arr.begin(), arr.end(), r);
                int planets = distance(left, right);
                ans += planets - 1;
            }
        }

        cout << "got ";
        cout << ans << endl;
    }
}

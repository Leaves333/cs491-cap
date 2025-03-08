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

struct FenwickTree {

    vll tree;
    int n;

    FenwickTree(int n) {
        this->n = n;
        tree.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += tree[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, ll delta) {
        for (; idx < n; idx = idx | (idx + 1))
            tree[idx] += delta;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    
    FenwickTree ftree(n);
    while (m--) {
        int x, v;
        cin >> x >> v;
        x--;

        ftree.add(x, v);
        cout << ftree.tree[x] << endl;
    }
}

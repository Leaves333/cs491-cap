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

    vvll tree;
    int w, h;

    FenwickTree(int w, int h) {
        this->w = w;
        this->h = h;
        tree.assign(w, vll(h));
    }

    int sum(int x, int y) {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += tree[i][j];
        return ret;
    }

    void add(int x, int y, int delta) {
        for (int i = x; i < w; i = i | (i + 1))
            for (int j = y; j < h; j = j | (j + 1))
                tree[i][j] += delta;
    }

};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, w, h, k, c;
    cin >> n >> w >> h >> k >> c;

    FenwickTree ftree(w, h);
    vector<pii> locations;
    while (n--) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        ftree.add(x, y, 1);
        locations.push_back({x, y});
    }

    ll ans = 0;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            ll coins = ftree.sum(i, j);
            ll profit = coins * k;
            ll cost = (i + 1) * (j + 1) * c;
            ans = max(ans, profit - cost);
        }
    }
    cout << ans << endl;
}

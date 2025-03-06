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

struct SegmentTree {

    vll tree;

    // public function to build segtree:
    // a: input array
    void build(const vll &a) { tree.resize(4 * a.size());
        build(a, 1, 0, a.size()-1);
    }

    // recursive function to build the segment tree:
    // a: input array
    // v: current index
    // tl: left boundary of current seg
    // tr: right boundary of current seg
    void build(const vll &a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);

            // your operation goes here
            tree[v] = max(tree[v*2], tree[v*2+1]);
        }
    }

    // recursive function to answer a query from l to r
    // call with v=1, tl=0, tr=n-1, l, r
    // v: current index
    // tl: left boundary of current seg
    // tr: right boundary of current seg
    // l: left bound of query
    // r: right bound of query
    ll query(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return 0;
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
    
        // your operation goes here
        return max(query(v*2, tl, tm, l, min(r, tm)),
                query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    // recursive function to update a value
    // call with v=1, tl=0, tr=n-1, pos, new_val
    // v: current index
    // tl: left boundary of current seg
    // tr: right boundary of current seg
    // l: target position
    // r: value to update
    void update(int v, int tl, int tr, int pos, ll new_val) {
        if (tl == tr) {
            tree[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, new_val);
            else
                update(v*2+1, tm+1, tr, pos, new_val);

            // your operation goes here
            tree[v] = max(tree[v*2], tree[v*2+1]);
        }
    }

};


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    int q; cin >> q;

    vll nums(n);
    SegmentTree seg_tree;
    seg_tree.build(nums);

    while (q--) {
        string s;
        ll a, b;
        cin >> s >> a >> b;
        
        if (s == "Add") {
            ll cur = seg_tree.query(1, 0, n-1, a-1, a-1);
            seg_tree.update(1, 0, n-1, a-1, cur + b);
        } else if (s == "Set") {
            seg_tree.update(1, 0, n-1, a-1, b);
        } else {
            cout << seg_tree.query(1, 0, n-1, a-1, b-1) << endl;
        }
    }
}

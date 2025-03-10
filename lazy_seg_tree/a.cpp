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

    int n; // size of the seg tree
    vll nums; // stores the base nums used to build the tree
    
    vll tree;
    vll lazy; // annotations for lazy updating of values

    // left child of p
    int l(int p) { return p << 1; }

    // right child of p
    int r(int p) { return (p << 1) | 1; }

    ll func(ll a, ll b) {
        return min(a, b);
    }

    // helper function to propagate lazy annotations down into children
    void propagate(int p, int tl, int tr) {

        if (tl > tr)
            return;

        tree[p] += lazy[p]; // NOTE: what should the lazy flag do? change this
        
        // not a leaf, propagate the flag down
        if (tl != tr) {
            lazy[l(p)] += lazy[p];
            lazy[r(p)] += lazy[p];
        }

        lazy[p] = 0; // erase the lazy flag
    }

    void build(int p, int tl, int tr) {

        /*cout << "node " << p << " covers from ";*/
        /*cout << tl << " to " << tr << endl;*/

        // base case
        if (tl == tr) {
            tree[p] = nums[tl];
        }

        // build subtrees
        else {
            int tm = (tl + tr) / 2;
            build(l(p), tl, tm);
            build(r(p), tm + 1, tr);
            tree[p] = func(tree[l(p)], tree[r(p)]);
        }

    }

    // public function to construct segtree:
    // O(n) to build the tree
    void init_tree(const vll &a) {

        // set some private variables
        nums = a;
        n = nums.size();
        tree.resize(n * 4);
        lazy.assign(n * 4, 0);

        // build the segtree from the root node
        build(1, 0, n-1);

    }

    ll query(int p, int tl, int tr, const int left, const int right) {

        propagate(p, tl, tr); // deal with lazy flag
        
        // impossible query
        if (left > right)
            return INT_MAX;

        // found the segment
        if (tl >= left && tr <= right)
            return tree[p];

        // recurse into left and right subtrees
        int tm = (tl + tr) / 2;
        return func(query(l(p), tl, tm, left, min(tm, right)),
                    query(r(p), tm + 1, tr, max(left, tm + 1), right));

    }
    
    // public function to query from left to right:
    // O(log n) to perform a query
    ll query(const int left, const int right) {
        return query(1, 0, n - 1, left, right);
    }

    
    void update(int p, int tl, int tr, const int left, const int right, const ll val) {

        // impossible range
        if (left > right)
            return;

        // found the segment
        if (tl >= left && tr <= right) {
            // update this node
            lazy[p] += val; 
            propagate(p, tl, tr);
        }

        // recurse into left and right subtrees
        else {
            int tm = (tl + tr) / 2;
            update(l(p), tl, tm, left, min(tm, right), val);
            update(r(p), tm+1, tr, max(left, tm+1), right, val);

            // resolve lazy flags if there are any, then update
            propagate(l(p), tl, tm);
            propagate(r(p), tm + 1, tr);

            tree[p] = func(tree[l(p)], tree[r(p)]);
        }

    }

    // public function to update nodes from left to right by val
    void update(const int left, const int right, const ll val) {
        update(1, 0, n - 1, left, right, val);
    }

    void print() {
        cout << "here's tree!" << endl;
        for (int i = 0; i < tree.size(); i++) {
            cout << i << "\t";
        }
        cout << endl;
        for (int i = 0; i < tree.size(); i++) {
            cout << tree[i] << "\t";
        }
        cout << endl;
        cout << endl;
    }

};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    getline(cin, s);
    int n = stoi(s);

    vll nums(n);
    getline(cin, s);
    int idx = 0;
    for (int i = 0; i < n; i++) {
        auto next = s.find(" ", idx);
        if (next == string::npos) {
            nums[i] = stoi(s.substr(idx));
        } else {
            nums[i] = stoi(s.substr(idx, next - idx));
            idx = next + 1;
        }
    }

    SegmentTree segtree;
    segtree.init_tree(nums);
    /*segtree.print();*/

    int m;
    getline(cin, s);
    m = stoi(s);

    while (m--) {
        getline(cin, s);
        int a, b, c;

        idx = 0;
        auto next = s.find(" ", idx);
        a = stoi(s.substr(idx, next - idx));
        idx = next + 1;
        next = s.find(" ", idx);
        b = stoi(s.substr(idx, next - idx));
        idx = next + 1;

        if (idx == 0) {
            // do rmq operation
            if (b < a) {
                ll first = segtree.query(0, b);
                ll second = segtree.query(a, segtree.n-1);
                cout << min(first, second) << endl;
            } else {
                cout << segtree.query(a, b) << endl;
            }
        } else {
            // do inc operation
            c = stoi(s.substr(idx));
            if (b < a) {
                segtree.update(0, b, c);
                segtree.update(a, segtree.n-1, c);
            } else {
                segtree.update(a, b, c);
            }
            /*segtree.print();*/

        }

    }

}

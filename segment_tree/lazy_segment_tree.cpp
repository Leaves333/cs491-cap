#include <algorithm>
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
    vll tree; // stores the actual segment tree
    vll lazy; // annotations for lazy updating of values

    // left child of p
    int l(int p) { return p << 1; }

    // right child of p
    int r(int p) { return (p << 1) + 1; }

    // operation we want the seg tree to do
    ll func(ll a, ll b) {
        if (a == -1) return b;
        if (b == -1) return a;
        return max(a, b); // NOTE: what operation do you want? change this
    }

    // helper function to propagate lazy annotations down into children
    void propagate(int p, int tl, int tr) {

        if (tl > tr)
            return;

        // no lazy flag on this node, don't do anything
        if (lazy[p] == -1)
            return;

        tree[p] = lazy[p]; // NOTE: what should the lazy flag do? change this
        
        // not a leaf, propagate the flag down
        if (tl != tr) {
            lazy[l(p)] = lazy[p];
            lazy[r(p)] = lazy[p];
        }

        // is a leaf, time to update
        else {
            nums[tl] = lazy[p]; // NOTE: what should the lazy flag do?
        }

        lazy[p] = -1; // erase the lazy flag
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
        lazy.assign(n * 4, -1);

        // build the segtree from the root node
        build(1, 0, n-1);

    }

    ll query(int p, int tl, int tr, const int left, const int right) {

        // impossible query
        if (left > right)
            return 0;

        // found the segment
        if (left == tl && right == tr)
            return tree[p];

        // recurse into left and right subtrees
        propagate(p, tl, tr); // deal with lazy flag
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
        if (tl == left && tr == right) {
            lazy[p] = val; // update this node
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

        cout << "printing the segtree: " << endl;

        cout << "here's the tree: " << endl;
        for (int i = 0; i < tree.size(); i++) {
            cout << i << "\t";
        }
        cout << endl;
        for (int i = 0; i < tree.size(); i++) {
            cout << tree[i] << "\t";
        }
        cout << endl;

        cout << "here's the lazy: " << endl;
        for (int i = 0; i < lazy.size(); i++) {
            cout << i << "\t";
        }
        cout << endl;
        for (int i = 0; i < lazy.size(); i++) {
            cout << lazy[i] << "\t";
        }
        cout << endl;

    }

};

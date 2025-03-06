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
    
    vll max_tree;
    vll sum_tree;
    vll lazy; // annotations for lazy updating of values

    // left child of p
    int l(int p) { return p << 1; }

    // right child of p
    int r(int p) { return (p << 1) + 1; }

    // operation we want the seg tree to do
    ll add(ll a, ll b) {
        return a + b; // NOTE: what operation do you want? change this
    }

    // helper function to propagate lazy annotations down into children
    void propagate(int p, int tl, int tr) {

        if (tl > tr)
            return;

        max_tree[p] += lazy[p]; // NOTE: what should the lazy flag do? change this
        sum_tree[p] += lazy[p] * (tr - tl + 1);
        
        // not a leaf, propagate the flag down
        if (tl != tr) {
            lazy[l(p)] += lazy[p];
            lazy[r(p)] += lazy[p];
        }

        // is a leaf, time to update
        else {
            nums[tl] += lazy[p]; // NOTE: what should the lazy flag do?
        }

        lazy[p] = 0; // erase the lazy flag
    }

    void build(int p, int tl, int tr) {

        /*cout << "node " << p << " covers from ";*/
        /*cout << tl << " to " << tr << endl;*/

        // base case
        if (tl == tr) {
            max_tree[p] = nums[tl];
            sum_tree[p] = nums[tl];
        }

        // build subtrees
        else {
            int tm = (tl + tr) / 2;
            build(l(p), tl, tm);
            build(r(p), tm + 1, tr);
            max_tree[p] = max(max_tree[l(p)], max_tree[r(p)]);
            sum_tree[p] = add(sum_tree[l(p)], sum_tree[r(p)]);
        }

    }

    // public function to construct segtree:
    // O(n) to build the tree
    void init_tree(const vll &a) {

        // set some private variables
        nums = a;
        n = nums.size();
        max_tree.resize(n * 4);
        sum_tree.resize(n * 4);
        lazy.assign(n * 4, 0);

        // build the segtree from the root node
        build(1, 0, n-1);

    }

    ll query_max(int p, int tl, int tr, const int left, const int right) {

        propagate(p, tl, tr); // deal with lazy flag
        
        // impossible query
        if (left > right)
            return 0;

        // found the segment
        if (left == tl && right == tr)
            return max_tree[p];

        // recurse into left and right subtrees
        int tm = (tl + tr) / 2;
        return max(query_max(l(p), tl, tm, left, min(tm, right)),
                    query_max(r(p), tm + 1, tr, max(left, tm + 1), right));

    }
    
    // public function to query from left to right:
    // O(log n) to perform a query
    ll query_max(const int left, const int right) {
        return query_max(1, 0, n - 1, left, right);
    }

    ll query_sum(int p, int tl, int tr, const int left, const int right) {

        propagate(p, tl, tr); // deal with lazy flag

        // impossible query
        if (left > right)
            return 0;

        // found the segment
        if (left == tl && right == tr)
            return sum_tree[p];

        // recurse into left and right subtrees
        int tm = (tl + tr) / 2;
        return add(query_sum(l(p), tl, tm, left, min(tm, right)),
                    query_sum(r(p), tm + 1, tr, max(left, tm + 1), right));

    }
    
    // public function to query from left to right:
    // O(log n) to perform a query
    ll query_sum(const int left, const int right) {
        return query_sum(1, 0, n - 1, left, right);
    }

    void update(int p, int tl, int tr, const int left, const int right, const ll val) {

        // impossible range
        if (left > right)
            return;

        // found the segment
        if (tl == left && tr == right) {
            // update this node
            if (lazy[0] == -1)
                lazy[p] = val;
            else
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

            max_tree[p] = max(max_tree[l(p)], max_tree[r(p)]);
            sum_tree[p] = add(sum_tree[l(p)], sum_tree[r(p)]);
        }

    }

    // public function to update nodes from left to right by val
    void update(const int left, const int right, const ll val) {
        update(1, 0, n - 1, left, right, val);
    }

    void print() {

        cout << "printing the segtree: " << endl;

        cout << "here's max tree: " << endl;
        for (int i = 0; i < max_tree.size(); i++) {
            cout << i << "\t";
        }
        cout << endl;
        for (int i = 0; i < max_tree.size(); i++) {
            cout << max_tree[i] << "\t";
        }
        cout << endl;

        cout << "here's sum tree: " << endl;
        for (int i = 0; i < sum_tree.size(); i++) {
            cout << i << "\t";
        }
        cout << endl;
        for (int i = 0; i < sum_tree.size(); i++) {
            cout << sum_tree[i] << "\t";
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

        cout << endl;

    }

};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    SegmentTree segtree;
    vll nums(n, 0);
    segtree.init_tree(nums);

    while (q--) {

        string op;
        int l, r;
        cin >> op >> l >> r;
        l--; r--; // tree is 0 indexed, but input is 1 indexed

        if (op == "Add") {
            int v; cin >> v;
            segtree.update(l, r, v);
        } else if (op == "Max") {
            cout << segtree.query_max(l, r) << endl;
        } else if (op == "Sum") {
            cout << segtree.query_sum(l, r) << endl;
        }

    }
}

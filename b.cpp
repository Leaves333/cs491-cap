#include <algorithm>
#include <utility>
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
    
    vll min_tree;
    vll max_tree;
    vll lazy; // annotations for lazy updating of values
    
    vector<bool> valid; // stores whether each node is a root of a valid bst
    int bad_nodes; // stores how many elments are false in valid

    // left child of p
    int l(int p) { return p << 1; }

    // right child of p
    int r(int p) { return (p << 1) | 1; }

    // helper function to propagate lazy annotations down into children
    void propagate(int p, int tl, int tr) {

        if (tl > tr)
            return;

        min_tree[p] += lazy[p]; // NOTE: what should the lazy flag do? change this
        max_tree[p] += lazy[p]; // NOTE: what should the lazy flag do? change this
        
        // not a leaf, propagate the flag down
        if (tl != tr) {
            lazy[l(p)] += lazy[p];
            lazy[r(p)] += lazy[p];
        }

        lazy[p] = 0; // erase the lazy flag
    }

    void build(int p, int tl, int tr) {

        // base case
        if (tl == tr) {
            min_tree[p] = nums[tl];
            max_tree[p] = nums[tl];
        }

        // build subtrees
        else {
            int tm = (tl + tr) / 2;
            build(l(p), tl, tm);
            build(r(p), tm + 1, tr);
            min_tree[p] = min(min_tree[l(p)], min_tree[r(p)]);
            max_tree[p] = max(max_tree[l(p)], max_tree[r(p)]);
        }

    }

    // public function to construct segtree:
    // O(n) to build the tree
    void init_tree(const vll &a) {

        // set some private variables
        nums = a;
        n = nums.size();
        min_tree.resize(n * 4);
        max_tree.resize(n * 4);
        lazy.assign(n * 4, 0);
        valid.assign(n * 4, true);
        bad_nodes = 0;

        // build the segtree from the root node
        build(1, 0, n-1);

    }

    ll query_max(int p, int tl, int tr, const int left, const int right) {

        propagate(p, tl, tr); // deal with lazy flag
        
        // impossible query
        if (left > right)
            return INT_MIN;

        // found the segment
        if (tl >= left && tr <= right)
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

    ll query_min(int p, int tl, int tr, const int left, const int right) {

        propagate(p, tl, tr); // deal with lazy flag
        
        // impossible query
        if (left > right)
            return INT_MAX;

        // found the segment
        if (tl >= left && tr <= right)
            return min_tree[p];

        // recurse into left and right subtrees
        int tm = (tl + tr) / 2;
        return min(query_min(l(p), tl, tm, left, min(tm, right)),
                    query_min(r(p), tm + 1, tr, max(left, tm + 1), right));

    }
    
    // public function to query from left to right:
    // O(log n) to perform a query
    ll query_min(const int left, const int right) {
        return query_min(1, 0, n - 1, left, right);
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

            max_tree[p] = max(max_tree[l(p)], max_tree[r(p)]);
        }

    }

    // public function to update nodes from left to right by val
    void update(const int left, const int right, const ll val) {
        update(1, 0, n - 1, left, right, val);
    }

    void print() {
        cout << "here's tree!" << endl;
        for (int i = 0; i < max_tree.size(); i++) {
            cout << i << "\t";
        }
        cout << endl;
        for (int i = 0; i < max_tree.size(); i++) {
            cout << max_tree[i] << "\t";
        }
        cout << endl;
        cout << endl;
    }

};

// do an inorder traversal of the tree
pii dfs(int x, int p, const vll &nums, const vvi &edges, vll &ordering, vector<pii> &ranges) {

    int left = INT_MAX;
    int right = INT_MIN;

    for (auto dest : edges[x]) {
        if (dest != p && nums[dest] < nums[x]) {
            auto bounds = dfs(dest, x, nums, edges, ordering, ranges);
            left = min(left, bounds.first);
            right = max(right, bounds.second);
        }
    }

    left = min(left, (int) ordering.size());
    right = max(right, (int) ordering.size());
    ordering.push_back(nums[x]);

    for (auto dest : edges[x]) {
        if (dest != p && nums[dest] > nums[x]) {
            auto bounds = dfs(dest, x, nums, edges, ordering, ranges);
            left = min(left, bounds.first);
            right = max(right, bounds.second);
        }
    }
    
    ranges[x] = {left, right};
    return {left, right};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vll nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vvi edges(n);
    for (int i = 1; i < n; i++) {
        int x; cin >> x;
        x--;
        edges[i].push_back(x);
        edges[x].push_back(i);
    }

    vector<pii> ranges(n);
    vll ordering;
    dfs(0, -1, nums, edges, ordering, ranges);

    SegmentTree segtree;
    segtree.init_tree(ordering);

    while (m--) {
        char op;
        int v, k;
        cin >> op >> v >> k;

        
    }
}

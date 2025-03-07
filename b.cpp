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
    vll left;
    vll right;

    // public function to build segtree: a: input array
    void build(const vll &a) {
        tree.resize(4 * a.size());
        left.resize(4 * a.size());
        right.resize(4 * a.size());
        build(a, 1, 0, a.size()-1);
    }

    int l(int v) { return v * 2; }
    int r(int v) { return (v * 2) + 1; }

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
            // combine both largest segments of children
            tree[v] = tree[l(v)] + tree[r(v)] + right[l(v)] + left[r(v)];
            left[v] = left[l(v)];
            right[v] = right[r(v)];

            // if left segment is better
            if (tree[l(v)] > tree[v]) {
                tree[v] = tree[l(v)];
                right[v] = right[r(v)] + tree[r(v)] + left[r(v)] + right[l(v)];
            }

            // if right segment is better
            if (tree[r(v)] > tree[v]) {
                tree[v] = tree[r(v)];
                left[v] = left[l(v)] + tree[l(v)] + right[l(v)] + left[r(v)];
            }
        }

        /*cout << "building tree: " << endl;*/
        /*cout << v << " goes from " << tl << " to " << tr << ", ";*/
        /*cout << "left=" << left[v] << ", ";*/
        /*cout << "tree=" << tree[v] << ", ";*/
        /*cout << "right=" << right[v] << endl;*/

    }

    // recursive function to answer a query from l to r
    // call with v=1, tl=0, tr=n-1, l, r
    // v: current index
    // tl: left boundary of current seg
    // tr: right boundary of current seg
    // l: left bound of query
    // r: right bound of query
    array<ll, 3> query(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return array<ll, 3>();
        if (l == tl && r == tr) {
            return {left[v], tree[v], right[v]};
        }
        int tm = (tl + tr) / 2;
    
        auto left_query = query(v*2, tl, tm, l, min(r, tm));
        auto right_query = query(v*2+1, tm+1, tr, max(l, tm+1), r);

        array<ll, 3> answer;
        // your operation goes here
        // combine both largest segments of children
        answer[1] = left_query[1] + right_query[1] + left_query[2] + right_query[0];
        answer[0] = left_query[0];
        answer[2] = right_query[2];

        // if left segment is better
        if (left_query[1] > answer[1]) {
            answer[1] = left_query[1];
            answer[2] = right_query[2] + right_query[1] + right_query[0] + left_query[2];
        }

        // if right segment is better
        if (right_query[1] > answer[1]) {
            answer[1] = right_query[1];
            answer[0] = left_query[0] + left_query[1] + left_query[2] + right_query[0];
        }

        /*cout << "query at " << tl << " to " << tr << " returned ";*/
        /*cout << answer[0] << ", ";*/
        /*cout << answer[1] << ", ";*/
        /*cout << answer[2] << endl;*/

        return answer;
    }

};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vll nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    SegmentTree segtree;
    segtree.build(nums);

    ll ans = 0;
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        ll query = segtree.query(1, 0, n-1, l, r)[1];
        cout << query << endl;
        ans += max(0ll, query);
    }
    cout << ans << endl;
}

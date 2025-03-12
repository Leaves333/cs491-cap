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

struct node {
    ll ans;
    ll sum;
    ll left;
    ll right;
};

struct SegmentTree {

    vll ans;
    vll sum;
    vll left;
    vll right;

    // public function to build segtree: a: input array
    void build(const vll &a) {
        ans.resize(4 * a.size());
        sum.resize(4 * a.size());
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
            ans[v] = a[tl];
            sum[v] = a[tl];
            left[v] = a[tl];
            right[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);

            // combine both largest segments of children
            ans[v] = max(right[l(v)] + left[r(v)], max(ans[l(v)], ans[r(v)]));
            sum[v] = sum[l(v)] + sum[r(v)];
            left[v] = max(left[l(v)], sum[l(v)] + left[r(v)]);
            right[v] = max(right[r(v)], sum[r(v)] + right[l(v)]);
        }

        cout << "building tree: " << endl;
        cout << v << " goes from " << tl << " to " << tr << ", ";
        cout << "ans=" << ans[v] << ", ";
        cout << "sum=" << sum[v] << ", ";
        cout << "left=" << left[v] << ", ";
        cout << "right=" << right[v] << endl;

    }

    // recursive function to answer a query from l to r
    // call with v=1, tl=0, tr=n-1, l, r
    // v: current index
    // tl: left boundary of current seg
    // tr: right boundary of current seg
    // l: left bound of query
    // r: right bound of query
    node query(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return node();
        if (l == tl && r == tr) {
            return {left[v], ans[v], right[v]};
        }
        int tm = (tl + tr) / 2;
    
        auto left_query = query(v*2, tl, tm, l, min(r, tm));
        auto right_query = query(v*2+1, tm+1, tr, max(l, tm+1), r);

        node answer;
        answer.ans = max(left_query.right + right_query.left, max(left_query.ans, right_query.ans));
        answer.sum = left_query.sum + right_query.sum;
        answer.left = max(left_query.left, left_query.sum + right_query.left);
        answer.right = max(right_query.right, right_query.sum + left_query.right);

        cout << "query from tl=" << tl << " to tr=" << tr << "returned";

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

        ll query = segtree.query(1, 0, n-1, l, r).ans;
        cout << max(0ll, query) << endl;
        ans += max(0ll, query);
    }
    cout << ans << endl;
}

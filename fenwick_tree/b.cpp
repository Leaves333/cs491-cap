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

struct query {
    int l, r, idx, ans;
};

bool sort_by_idx(const query &first, const query &second) {
    return first.idx < second.idx;
}

bool sort_by_r(const query &first, const query &second) {
    return first.r < second.r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vll nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<query> queries;  
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        queries.push_back(query{l, r, i, -1});
    }
    
    sort(queries.begin(), queries.end(), sort_by_r);
    FenwickTree ftree(n + 1);
    map<int, int> previously_seen;
    int idx = 0;
    for (query &q : queries) {
        while (idx < q.r) {
            if (previously_seen.count(nums[idx])) {
                ftree.add(previously_seen[nums[idx]], -1);
            }
            previously_seen[nums[idx]] = idx;
            ftree.add(idx, 1);
            idx++;
        }

        /*cout << "ftree is now: " << endl;*/
        /*for (int i = 0; i < ftree.tree.size(); i++) {*/
        /*    cout << i << "\t";*/
        /*}*/
        /*cout << endl;*/
        /*for (int i = 0; i < ftree.tree.size(); i++) {*/
        /*    cout << ftree.tree[i] << "\t";*/
        /*}*/
        /*cout << endl;*/

        q.ans = ftree.sum(q.l - 1, q.r);
    }

    sort(queries.begin(), queries.end(), sort_by_idx);
    for (query q : queries) {
        cout << q.ans << endl;
    }

}

#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using vl = vector<ll>;

vector<ll> lazy;

struct node {
    ll max;
    ll sum;
};

int getMid(int l, int r) {
    return l + (r - l) / 2;
}

// ss - starting index of segment tree
// se - ending index of segment tree
// qs - starting index of query
// qe - ending index of query
struct node MaxUntill(struct node* st, int ss, int se, int qs, int qe, int si) {
    struct node temp, left, right;
    if (lazy[si] != 0) {
        st[si].max += lazy[si];
        if (ss != se) {
            lazy[2 * si + 1] += lazy[si];
            lazy[2 * si + 2] += lazy[si];
        }
        lazy[si] = 0;   
    }
    if (ss > se || ss > qe || se < qs) { //out of range
        temp.max = 0;
        return temp;
    } 

    // if segment is in range, return the node
    if (qs <= ss && qe >= se) {
        return st[si];
    }

    // if part of the segment is in range
    int mid = getMid(ss, se);
    left = MaxUntill(st, ss, mid, qs, qe, 2 * si + 1);
    right = MaxUntill(st, mid + 1, se, qs, qe, 2 * si + 2);

    temp.max = max(left.max, right.max);
    return temp;
}

// si - index of current node in segment tree
void constructSTUtil(ll arr[], int ss, int se, struct node* st, int si) {
    if (ss == se) {
        st[si].max = arr[ss];
        st[si].sum = arr[ss];
        return; 
    }
    int mid = getMid(ss, se);
    constructSTUtil(arr, ss, mid, st, si * 2 + 1);
    constructSTUtil(arr, mid + 1, se, st, si * 2 + 2);
    st[si].max = max(st[si * 2 + 1].max, st[si * 2 + 2].max);
    st[si].sum = st[si * 2 + 1].sum + st[si * 2 + 2].sum;
}

struct node* constructST(ll arr[], int n) {
    int height = (int)(ceil(log2(n)));
    int maxSize = 2 * (int)pow(2, height) - 1;
    struct node* st = new struct node[maxSize];
    constructSTUtil(arr, 0, n - 1, st, 0);
    return st;
}

// updating a range
// qs - query start
// qe - query end
// add - amount to add
// si - segment index
void update(struct node* st, int ss, int se, int qs, int qe, ll add, int si) {
    if (lazy[si] != 0) {
        st[si].max += lazy[si];
        st[si].sum += lazy[si] * (se - ss + 1);
        if (ss != se) {
            lazy[2 * si + 1] += lazy[si];
            lazy[2 * si + 2] += lazy[si];
        }
        lazy[si] = 0;
    }   
    if (ss > se || ss > qe || se < qs) {
        return;
    } 
    if (ss >= qs && se <= qe) {
        st[si].max += add;
        st[si].sum += add * (se - ss + 1);

        if (ss != se) {
            lazy[2 * si + 1] += add;
            lazy[2 * si + 2] += add;
        }
        return;     
    }

    int mid = getMid(ss, se);
    update(st, ss, mid, qs, qe, add, 2 * si + 1);
    update(st, mid + 1, se, qs, qe, add, 2 * si + 2);

    st[si].max = max(st[2 * si + 1].max, st[2 * si + 2].max);
    st[si].sum = st[2 * si + 1].sum + st[2 * si + 2].sum;
    
}

ll getSum(struct node* st, int ss, int se, int qs, int qe, int si) {
    if (lazy[si] != 0) {
        st[si].sum += lazy[si] * (se - ss + 1);
        if (ss != se) {
            lazy[2 * si + 1] += lazy[si];
            lazy[2 * si + 2] += lazy[si];
        }
        lazy[si] = 0;   
    }
    if (ss > se || ss > qe || se < qs) {
        return 0;
    } 

    if (ss>=qs && se<=qe) {
        return st[si].sum;
    }
    int mid = getMid(ss, se);
    return getSum(st, ss, mid, qs, qe, 2*si+1) + getSum(st, mid+1, se, qs, qe, 2*si+2);
}
int main() {    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k; 
    cin >> n >> k;

    ll* arr = new ll[n]();
     // if lazy[i] == 0, there are no pending changes, 
                            // otherwise, lazy[i] stands for the amount that needs to be added to node i 
    fill_n(arr, n, 0);
    lazy.resize(4 * n, 0); // needs 4 * n nodes in worst case 

    struct node* segmentTree = constructST(arr, n); 

    while (k--) {
        string str;
        ll l, r;
        cin >> str >> l >> r;
        l--;
        r--;
        // cout << str << endl;
        if (str == "Add") {
            ll v;
            cin >> v;

            update(segmentTree, 0, n - 1, l, r, v, 0);
        } else if (str == "Max") {
            cout << MaxUntill(segmentTree, 0, n - 1, l, r, 0).max << "\n";
        } else if (str == "Sum") {
            cout << getSum(segmentTree, 0, n - 1, l, r, 0) << "\n";
        }
    }
}

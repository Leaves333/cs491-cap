#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <cmath>
#include <iostream>
#include <map>
using namespace std;
typedef long long ll;
using vl = vector<ll>;

int n;
int block_size;
vl original_arr;
vl block;
map<int, int> block_sizes; // index, size of block
vl intervals; // this will keep the left end of the intervals

ll lowbit(ll x) {
    return x & -x;
}

ll query(int l, int r) {
    ll sum = 0;
    int curr = -1;
    int i = 0;

    // first block that can be used
    while (i + 1 < intervals.size() && intervals[i + 1] <= l) {
        i++;
    }

    // first block (partial sum before a full block starts)
    bool used = false;
    while (l < intervals[i]) {
        sum += original_arr[l] * curr;
        l++;
        used = true;
    }

    if (used) {
        curr *= -1;
    }

    // overlapping middle blocks
    used = false;
    while (l < intervals.size() && intervals[i] + block_sizes[intervals[i]] <= r) {
        sum += block[intervals[i]] * curr;
        l += block_sizes[intervals[i]];
        i++;
        curr *= -1;
        used = true;
    }

    if (!used) {
        curr = -1;
    }
    // last block
    while (l <= r) {
        sum += original_arr[l] * curr;
        l++;
    }
    return sum;
}

ll brute_force_query(int l, int r) {
    ll ret = 0;
    for (int i = l; i <= r; i++) {
        // we have to add 1 because we subtract 1 from the indices
        // before calling this function
        ll arg = (l + 1) ^ ((i + 1) / block_size);
        ll exp = lowbit(arg);

        if (exp % 2 == 0)
            ret += original_arr[i];
        else
            ret += original_arr[i] * -1;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m;
    block_size = sqrt(n);
    original_arr.resize(n);
    block.resize(n);
    for (int i = 0; i < n; i++) {
        ll temp;
        cin >> temp;
        original_arr[i] = temp;
    }


    // making the blocks
    int prev = 0;
    int size = 0;
    int block_index = -1;
    intervals.push_back(0);  
    for (int i = 0; i < n; i++) {  
        block_index = floor((i + 1) / sqrt(n));  
        block[block_index] += original_arr[i];  
    
        if (block_index != prev) {  
            intervals.push_back(i);  
            block_sizes[prev] = size;  
            size = 0;
            prev = block_index;
        }
        size++;
    }
    block_sizes[prev] = size;


    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        cout << "query says " << query(l - 1, r - 1) << endl;
        cout << "brute force says " << brute_force_query(l - 1, r - 1) << endl;
    }

    
}

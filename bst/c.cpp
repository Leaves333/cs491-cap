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

const int NUM_VERTICES = 1001;
vi original_values(NUM_VERTICES);
vi values(NUM_VERTICES);
vi parent(NUM_VERTICES);
vvi children(NUM_VERTICES);

bool validate_bst(int root, int l, int r) {
    if (values[root] < l || values[root] > r)
        return false;
    for (int child : children[root]) {
        bool res = false;
        if (original_values[child] > original_values[root]) {
            res = validate_bst(child, values[root], r);
        } else {
            res = validate_bst(child, l, values[root]);
        }
        if (!res)
            return false;
    }
    return true;
}

void modify_tree(int root, int diff) {
    values[root] += diff;
    for (int child : children[root]) {
        modify_tree(child, diff);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> values[i];
        original_values[i] = values[i];
    }

    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        parent[i] = p;
        children[p].push_back(i);
    }

    while (m--) {
        char op;
        int v, k;
        cin >> op >> v >> k;

        if (op == '-') {
            modify_tree(v, k * -1);
        } else {
            modify_tree(v, k);
        }

        if (validate_bst(1, INT_MIN, INT_MAX)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

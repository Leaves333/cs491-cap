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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        bool found = false;
        vi list;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            list.push_back(x);
        }

        set<int> possible_sums;
        possible_sums.insert(0);

        for (int i = 0; i < list.size(); i++) {
            set<int> new_sums(all(possible_sums));
            for (auto x : possible_sums) {
                new_sums.insert(x + list[i]);
                new_sums.insert(x - list[i]);
                if (x + list[i] == 0 || x - list[i] == 0) {
                    found = true;
                }
            }
            possible_sums = new_sums;
        }

        if (found) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

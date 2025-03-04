#pragma optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;
        ll first = 0, second = 0;
        for (int i = 0; i < x; i++) {
            int k; cin >> k;
            first += k;
        }
        for (int i = 0; i < y; i++) {
            int k; cin >> k;
            second += k;
        }
        cout << first - second << endl;
    }
}

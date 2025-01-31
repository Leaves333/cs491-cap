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

    int n;
    ll a, b;
    cin >> n >> a >> b;
    
    ll MOD = 1000000007;

    bool good = true;
    for (int i = 0; i < n; i++) {
        a *= 3;
        if (a < 2 * b && a > b) {
            good = false;
            break;
        } else if (a >= 2 * b) {
            a -= 2 * b;
        }
    }

    if (good) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

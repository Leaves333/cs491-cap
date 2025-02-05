#include <algorithm>
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

    ll n, k;
    cin >> n >> k;
    int first, second;
    cin >> first >> second;

    vi x(first), y(second);
    for (int i = 0; i < first; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < second; i++) {
        cin >> y[i];
    }

    sort(x.begin(), x.end());
    reverse(x.begin(), x.end());
    sort(y.begin(), y.end());
    reverse(y.begin(), y.end());

    int a = 0, b = 0;
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        ans += x[a] + y[b];
        if (a >= x.size() - 1) {
            b++;
        }
    }
}

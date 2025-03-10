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

    ll n, c;
    cin >> n >> c;
    priority_queue<ll, vll, greater<ll>> pq;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        pq.push(x);
    }

    ll ans = c * (n - 1);
    while (pq.size() > 1) {
        ll first = pq.top();
        pq.pop();
        ll second = pq.top();
        pq.pop();
        ans += first + second;
        pq.push(first + second);
    }

    cout << ans << endl;
}

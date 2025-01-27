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

    int n; cin >> n;
    vi arr(n);
    vi ans(n, -1);
    stack<pii> s;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        while (!s.empty() && x > s.top().second) {
            ans[s.top().first] = i + 1;
            s.pop();
        }
        s.push(make_pair(i, x));
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

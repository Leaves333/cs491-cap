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

    if (k > n) {
        cout << "NO" << endl;
    } else if (k < __builtin_popcountll(n)) {
        cout << "NO" << endl;
    } else {
        priority_queue<ll> pq;
        for (int i = 0; i <= 31; i++) {
            if (n & 1 << i)
                pq.push(1 << i);
        }

        while (pq.size() < k) {
            ll top = pq.top();
            pq.pop();
            pq.push(top / 2);
            pq.push(top / 2);
        }

        cout << "YES" << endl;
        while (!pq.empty()) {
            cout << pq.top() << " ";
            pq.pop();
        }
        cout << endl;
    }
}

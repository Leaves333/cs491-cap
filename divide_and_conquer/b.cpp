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
    vector<pii> problems(n);

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        problems[i] = make_pair(y, x);
    }

    // deadline, time needed
    sort(all(problems));

    int low = -1, high = 86400;
    while (low < high) {
        int mid = low + (high - low + 1) / 2;
        int cur_time = mid;
        bool good = true;
        for (int i = 0; i < problems.size(); i++) {
            cur_time += problems[i].second;
            if (cur_time > problems[i].first) {
                good = false;
                break;
            }
        }

        if (good) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }

    cout << low << endl;
}

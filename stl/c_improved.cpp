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

    int n, m;
    cin >> n >> m;
    vi nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // maximum queue: biggest element in front, elements in decreasing order
    deque<int> q; 
    int lastl = 0, lastr = -1;
    while (m--) {

        // get input for the query
        int l, r;
        cin >> l >> r;

        // add elements to the queue
        for (int i = lastr + 1; i < r; i++) {
            // pop elements from the queue
            // to maintain the elements in decreasing order
            while (!q.empty() && q.back() < nums[i]) {
                q.pop_back();
            }
            q.push_back(nums[i]);
        }

        // remove elements from queue
        for (int i = lastl; i < l - 1; i++) {
            if (!q.empty() && q.front() == nums[i]) {
                q.pop_front();
            }
        }
        cout << q.front() << endl;

        lastr = r - 1;
        lastl = l - 1;
    }

}

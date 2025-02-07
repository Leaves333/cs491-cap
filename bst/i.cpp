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
    cin >> n;
    n--;
    set<int> nodes;
    int k; cin >> k;
    nodes.insert(k);

    map<int, int> heights;
    heights[k] = 0;

    while (n--) {
        int x; cin >> x;
        auto next = nodes.upper_bound(x); // element after x
        auto prev = next; // element before x
        prev--;

        if (next == nodes.end()) {
            cout << *prev << " ";
            heights[x] = heights[*prev] + 1;
        } else if (next == nodes.begin()) {
            cout << *next << " ";
            heights[x] = heights[*next] + 1;
        } else if (heights[*next] > heights[*prev]) {
            cout << *next << " ";
            heights[x] = heights[*next] + 1;
        } else {
            cout << *prev << " ";
            heights[x] = heights[*prev] + 1;
        }

        nodes.insert(x);

    }

    cout << endl;
}

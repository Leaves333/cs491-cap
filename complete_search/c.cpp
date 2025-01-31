#include <algorithm>
#include <array>
#include <climits>
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

struct pos {
    int x = 0;
    int y = 0;
};

set<array<int, 4>> seen;
ll ans = LLONG_MIN;

void search(pos player, pos mattox, int time) {
    if (time % 2 == 1) {
        
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    pos player, mattox;
    search(player, mattox, 1);
    if (ans == LLONG_MIN) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

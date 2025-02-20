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

struct edge {
    char type;
    int start_time, end_time;
    int dest;
};

struct city {
    int pf, pt, pc, ft, fc, tc;
};

struct state {
    int time;
};

bool operator<(const state &first, const state &second) {
    return first.time < second.time;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
}

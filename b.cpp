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

struct upgrade {
    int cost;
    int multi;
};

bool operator<(const upgrade &first, const upgrade &second) {
    return (first.cost + (double) second.cost / first.multi) < (second.cost + (double) first.cost / second.multi);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;
    vi c(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector<upgrade> upgrade_array;
    for (int i = 0; i < n; i++) {
        double good_ratio = ((double) p[i] - 1) / p[i];
        double actual_ratio = ((double) c[i]) / k;
        if (actual_ratio < good_ratio)
        /*if (k > ((double) k / p[i]) + c[i])*/
            upgrade_array.push_back({c[i], p[i]});
    }

    sort(upgrade_array.begin(), upgrade_array.end());
    double prod = 1;
    double time = 0;
    for (auto u : upgrade_array) {
        /*cout << "buying upgrade " << u.cost << ", " << u.multi << endl;*/
        time += u.cost / prod;
        prod *= u.multi;
    }

    cout << setprecision(15);
    cout << time + (k / prod) << endl;

}

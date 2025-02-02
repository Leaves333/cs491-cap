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

vector<array<int, 2>> lin_funcs;
vector<array<int, 3>> quad_funcs;
vector<array<int, 2>> sqrt_funcs;
vector<array<int, 2>> log_funcs;

double f(double t) {
    double res = 0.0;
    for (auto c : lin_funcs) {
        res += c[0] * t + c[1];
    }
    for (auto c : quad_funcs) {
        res += (c[0] * t * t) + (c[1] * t) + c[2];
    }
    for (auto c : sqrt_funcs) {
        res += sqrt(c[0] * t) + c[1];
    }
    for (auto c : log_funcs) {
        res += c[0] * log(t) + c[1];
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    while (n--) {
        string type;
        cin >> type;
        if (type == "1") {
            int a, b;
            cin >> a >> b;
            lin_funcs.push_back({a, b});
        } else if (type == "2") {
            int a, b, c;
            cin >> a >> b >> c;
            quad_funcs.push_back({a, b, c});
        } else if (type == "sqrt") {
            int a, b;
            cin >> a >> b;
            sqrt_funcs.push_back({a, b});
        } else if (type == "log") {
            int a, b;
            cin >> a >> b;
            log_funcs.push_back({a, b});
        }
    }

    // ternary search time
    int low = 0, high = 43200;
    while (high - low >= 3) {
        int m1 = low + (high - low) / 3;
        int m2 = high - (high - low) / 3;
        double f1 = f(m1);
        double f2 = f(m2);
        if (f1 < f2) {
            low = m1;
        } else {
            high = m2;
        }
    }

    vector<double> vals;
    for (int i = low; i <= high; i++) {
        vals.push_back(f(i));
    }

    double ans = vals[0];
    for (double d : vals) {
        ans = max(ans, d);
    }

    cout << ans << endl;

}

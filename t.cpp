#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
using vl = vector<ll>;
using vi = vector<int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    set<int> s;
    // key, amount of children
    map<int, int> map;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;

        s.insert(temp);
        map.insert({temp, 0});
        auto right = s.upper_bound(temp);
        auto left = (s.lower_bound(temp) == s.begin()) ? s.end() : prev(s.lower_bound(temp));

        if (s.size() == 1) {
            // root case
        } else if (right == s.end()) {
            map[*left]++;
            cout << *left << "\n";
        } else if (left == s.end()) {
            map[*right]++;
            cout << *right << "\n";
        } else {
            if (map[*left] > map[*right]) {
                cout << *right << "\n";
                map[*right]++;
            } else if (map[*left] < map[*right]) {
                cout << *left << "\n";
                map[*left]++;
            } else {
                if (abs(temp - *left) < abs(temp - *right)) {
                    cout << *left << "\n";
                    map[*left]++;
                } else {
                    cout << *right << "\n";
                    map[*right]++;
                }
            }
        }
    }
}

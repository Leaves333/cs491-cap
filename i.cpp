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

    int n, k;
    cin >> n >> k;
    vi a(n), pl(k), pr(k);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < k; i++) {
        cin >> pl[i];
    }
    for (int i = 0; i < k; i++) {
        cin >> pr[i];
    }

    vi w = a;
    sort(w.begin(), w.end());
    auto last = unique(w.begin(), w.end());
    w.erase(last, w.end());

    map<int, int> first_occurrence, last_occurrence;
    for (int i = 0; i < n; i++) {
        if (!first_occurrence.count(a[i]))
            first_occurrence[a[i]] = i;
        last_occurrence[a[i]] = i;
    }

    vi ql(k), qr(k);
    for (int i = 0; i < k; i++) {
        ql[i] = first_occurrence[w[pl[i]-1]];
    }
    for (int i = 0; i < k; i++) {
        qr[i] = last_occurrence[w[pr[i]-1]];
    }

    map<int, int> idx;
    for (int i = 0; i < k; i++) {
        idx[ql[i]] = i;
    }

    vi clean_arr(k, INT_MAX);
    for (int i = 0; i < k; i++) {
        if (idx.count(qr[i]))
            clean_arr[i] = idx[qr[i]];
    }
    
    vi lis(k, INT_MAX);
    for(int i : clean_arr) *upper_bound(all(lis), i - 1) = i;
    cout << lower_bound(all(lis), INT_MAX) - lis.begin() << endl;
    
}

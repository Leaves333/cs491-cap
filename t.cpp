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
    map<int, int> m;
    map<int, int> parent;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
 
        /*cout << "searching for temp=" << temp << endl;*/
 
        s.insert(temp);
        m.insert({temp, 0});
        auto right = s.upper_bound(temp);
        auto left = (s.lower_bound(temp) == s.begin()) ? s.end() : prev(s.lower_bound(temp));
 
        /*cout << "right is " << (right == s.end() ? "NULL" : to_string(*right)) << endl;*/
        /*cout << "left is " << (left == s.end() ? "NULL" : to_string(*left)) << endl;*/
        /*cout << "parent is... ";*/

        if (s.size() == 1) {
            // root case
            /*cout << endl;*/
        } else if (right == s.end()) {
            m[*left]++;
            parent[temp] = *left;
            cout << *left << " ";
            /*cout << endl;*/
        } else if (left == s.end()) {
            m[*right]++;
            parent[temp] = *right;
            cout << *right << " ";
            /*cout << endl;*/
        } else {
            if (m[*left] > m[*right]) {
                cout << *right << " ";
                /*cout << endl;*/
                m[*right]++;
                parent[temp] = *right;
            } else if (m[*left] < m[*right]) {
                cout << *left << " ";
                /*cout << endl;*/
                m[*left]++;
                parent[temp] = *left;
            } else {
                if (parent[*left] == *right) {
                    cout << *left << " ";
                    /*cout << endl;*/
                    m[*left]++;
                    parent[temp] = *left;
                } else {
                    cout << *right << " ";
                    /*cout << endl;*/
                    m[*right]++;
                    parent[temp] = *right;
                }
            }
        }
    }
    cout << endl;
}

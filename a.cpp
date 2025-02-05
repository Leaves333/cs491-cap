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

struct Node {
    int val;
    int num_children;
    Node *left, *right;
    Node(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    Node *head = nullptr;
    
    while (n--) {

        string op;
        ll x;
        cin >> op >> x;

        if (op == "Insert") {
            if (head == nullptr) {
                head = new Node(x);
                continue;
            }
        } else if (op == "Delete") {
            
        } else if (op == "Rank") {

        } else if (op == "Kth") {

        }
    }
}

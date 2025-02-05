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
        num_children = 1;
        left = nullptr;
        right = nullptr;
    }
};

void update_num_children(Node *cur) {
    cur->num_children = 1;
    if (cur->right != nullptr)
        cur->num_children += cur->right->num_children;
    if (cur->left != nullptr)
        cur->num_children += cur->left->num_children;
}

Node* insert(Node* cur, int x) {
    if (cur == nullptr) {
        return new Node(x);
    }
    if (x >= cur->val) {
        cur->right = insert(cur->right, x);
    }
    if (x < cur->val) {
        cur->left = insert(cur->left, x);
    }

    update_num_children(cur);
    return cur;
}

Node* del(Node* cur, int target) {

    if (cur == nullptr) {
        return cur;
    }

    // search for the node to be deleted
    if (target < cur->val) {
        cur->left = del(cur->left, target);
        update_num_children(cur);
    }

    else if (target > cur->val) {
        cur->right = del(cur->right, target);
        update_num_children(cur);
    }

    // found the node, delete it
    // node is a leaf
    else {

        // no children or only right child
        if (cur->left == nullptr) {
            Node* tmp = cur->right;
            delete cur;
            return tmp;
        }

        // only left child
        if (cur->right == nullptr) {
            Node* tmp = cur->left;
            delete cur;
            return tmp;
        }

        // both children exist
        // replace current node with successor
        // and delete the successor from the tree
        Node* successor = cur->right;
        while (successor != nullptr && successor->left != nullptr) {
            successor = successor->left;
        }
        cur->val = successor->val;
        cur->right = del(cur->right, successor->val);
        update_num_children(cur);
    }

    return cur;

}

int rank_node(Node* root, int x) {
    int ans = 0;
    Node* cur = root;
    while (cur != nullptr) {
        if (cur->val < x) {
            ans += 1;
            if (cur->left != nullptr)
                ans += cur->left->num_children;
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
    return ans;
}

// A utility function to do inorder tree traversal
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->val << "\t|\tchildren: " << root->num_children << endl;
        inorder(root->right);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    Node* root = nullptr;
    
    while (n--) {

        string op;
        ll x;
        cin >> op >> x;

        if (op == "Insert") {
            cout << "inserting " << x << "!!!" << endl;
            root = insert(root, x);
            inorder(root);
            cout << endl;
        } else if (op == "Delete") {
            cout << "deleting " << x << "!!!" << endl;
            root = del(root, x);
            cout << "head is now " << root->val << endl;
            inorder(root);
            cout << endl;
        } else if (op == "Rank") {
            cout << "rank with " << x << "!!!" << endl;
            cout << rank_node(root, x) << endl;
            cout << endl;
        } else if (op == "Kth") {

        }
    }
}

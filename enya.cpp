#include <string>
#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using vl = vector<ll>;
using vi = vector<int>;

struct node {
    ll value;
    node *parent, *left, *right;
    ll lCount; // amount of children in it's left subtree
    ll rCount;
};
void insert(node *add, node *curr) {
    // insert value is greater than
    if (add->value > curr->value) {
        if (curr->right == nullptr) {
            add->parent = curr;
            curr->right = add;
            curr->rCount++;
        } else {
            insert(add, curr->right);
            curr->rCount++;
        }
    } else { // insert value is less than
        if (curr->left == nullptr) {
            add->parent = curr;
            curr-> left = add;
            curr->lCount++;

        } else {
            insert(add, curr->left);
            curr->lCount++;

        }
    }
}
node* getSuccessor(node* curr){
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr)
        curr = curr->left;
    return curr;
}

node* remove (node *curr, ll val) {
    if (curr == nullptr) return curr;  // Base case: node not found

    // Searching for the node
    if (val < curr->value) {
        curr->left = remove(curr->left, val);
        curr->lCount--;
    } else if (val > curr->value) {
        curr->right = remove(curr->right, val);
        curr->rCount--;
    } else {
        // Case 1: No children
        if (curr->left == nullptr && curr->right == nullptr) {
            delete curr;
            return nullptr;
        }

        // Case 2: Only left child
        if (curr->right == nullptr) {
            node* temp = curr->left;
            temp->parent = curr->parent;
            delete curr;
            return temp;
        }

        // Case 3: Only right child
        if (curr->left == nullptr) {
            node* temp = curr->right;
            temp->parent = curr->parent;
            delete curr;
            return temp;
        }

        // Case 4: Two children (Replace with in-order successor)
        node* succ = getSuccessor(curr);
        curr->rCount--;
        curr->value = succ->value;
        curr->right = remove(curr->right, succ->value);
    }
    return curr;
}

ll kthSmallest(node* curr, ll k) {
    if (curr == nullptr) return -1;

    // Search left subtree
    if (k < curr->lCount+1) {
        return kthSmallest(curr->left, k);
    }

    // return curr node
    else if (k == curr->lCount+1) {
        return curr->value;
    }

    // decrement k by (lCount+1) and
    // search right subtree
    else {
        k = k - (curr->lCount+1);
        return kthSmallest(curr->right, k);
    }
}

ll findNode(node* curr, ll k) {
    int ans = 0;
    node* cur = curr;
    while (cur != nullptr) {
        if (cur->value < k) {
            ans += 1;
            if (cur->left != nullptr) {
                ans += 1 + cur->left->lCount + cur->left->rCount;
            }
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
    return ans;
}

void print_tree(node* curr) {

    if (curr == nullptr)
        return;

    print_tree(curr->left);

    cout << "val=" << curr->value;
    cout << ", left=" << ((curr->left == nullptr) ? "null" : to_string(curr->left->value));
    cout << ", right=" << ((curr->right == nullptr) ? "null" : to_string(curr->right->value));
    cout << ", parent=" << ((curr->parent == nullptr) ? "null" : to_string(curr->parent->value));
    cout << ", lcount=" << curr->lCount;
    cout << ", rcount=" << curr->rCount;
    cout << endl;

    print_tree(curr->right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;


    // source node found or not
    /*bool source = true;*/
    node *root = nullptr;
    for (int i = 0; i < n; i++) {
        string s;
        ll k;
        cin >> s >> k;
        node* temp = new node();
        if (s == "Insert") {
            // inserting a node
            if (root == nullptr) {
                root = temp;
                root->value = k;
                root->parent = nullptr;
                /*source = false;*/
            } else {
                temp->value = k;
                insert(temp, root);
            }
        } else if (s == "Delete") {
            // removing a node
            root = remove(root, k);

        } else if (s == "Kth") {
            // finding kth smallest element in bst
            ll kth = kthSmallest(root, k);
            if (kth == -1) {
                cout << "Wrong!" << endl;
            } else {
                cout << kth << endl;

            }
        } else if (s == "Rank") {
            // finding amount of elements smaller than k

            cout << findNode(root, k) << endl;
        }

        print_tree(root);
        cout << endl;

    }
}

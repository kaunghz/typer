#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void dfs_binary_tree(TreeNode* root) {
    if (root == nullptr) return;
    stack<TreeNode*> stack;
    stack.push(root);

    while (!stack.empty()) {
        TreeNode* node = stack.top();
        stack.pop();
        cout << node->val << " ";

        if (node->right) stack.push(node->right);
        if (node->left) stack.push(node->left);
    }
}
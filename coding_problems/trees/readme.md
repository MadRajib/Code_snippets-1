# Tree Problems

1. [In Order Traversal](#1-in-order-traversal)

### 1. In Order Traversal
- jmp left
- print node
- jmp right

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;

        traverse(root, res);

        return res;
    }

    void traverse(TreeNode* node, vector<int> &res) {
        // base
        if (!node)
            return;
        
        traverse(node->left, res);
        res.push_back(node->val);
        traverse(node->right, res);

        return;
    }
};
```
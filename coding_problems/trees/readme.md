# Tree Problems

1. [In Order Traversal](#1-in-order-traversal)
1. [Pre Order Traversal](#2-pre-order-traversal)

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

### 2. Pre order Traversal
- print node
- jmp left
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;

        traverse(root, res);

        return res;
    }

    void traverse(TreeNode *root, vector<int> &res) {
        if (!root)
            return;
        
        res.push_back(root->val);
        traverse(root->left, res);
        traverse(root->right, res);

        return;
    }
};
```

### 3. Post order traversal
- jmp left
- jmp right
- print node

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;

        traverse(root, res);

        return res;
    }

    void traverse(TreeNode* root, vector<int> &res) {
        if (!root)
            return;
        
        traverse(root->left, res);
        traverse(root->right, res);
        res.push_back(root->val);
        return;
    }
};
```

### 4. Invert Binary tree
- swap left right
- invert (left)
- invert (right)

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
    TreeNode* invertTree(TreeNode* root) {
        if (!root)
            return nullptr;

        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
};


```

### 5. Maximum Depth of Binary Tree
- 1 + max(left, right)

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
    int maxDepth(TreeNode* root) {
        return dfs(root);
    }

    int dfs(TreeNode* root) {
        if (!root)
            return 0;

        return 1 + max(dfs(root->left), dfs(root->right));
    }
};

```
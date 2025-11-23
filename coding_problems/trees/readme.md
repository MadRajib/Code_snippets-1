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

### 6. Diameter of Binary Tree
- dia = max(diag, left tree depth + right tree depth);

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
    int dia = 0;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return dia;   
    }

    int dfs(TreeNode* root) {
        if (!root)
            return 0;
        
        int lh = dfs(root->left);
        int rh = dfs(root->right);

        dia = max(dia, lh + rh);

        return 1 + max(lh, rh);
    }
};

```
### 7. Balanced Binary Tree
- use dfs
- return height and flag that indicates if subtree is balanced or not.
- left is balanced + right is balanced + currrent root is balanced -> then its balanced.

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
    bool isBalanced(TreeNode* root) {
        vector<int> res = dfs(root);

        return res[0] == 1;
    }

    vector<int> dfs(TreeNode *root) {
        //base
        if (!root)
            return {1, 0};
        vector<int> pl, pr;

        pl = dfs(root->left);
        pr = dfs(root->right);

        bool flag = pl[0] && pr[0] && (abs(pr[1] - pl[1]) <= 1);

        return {flag, 1 + max(pl[1], pr[1])};

    }
};

```

### 8. Same Tree
- if root both are null -> same
- move together left && right in both trees.

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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q)
            return true;
        
        if (p && q && (p->val == q->val)) {
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
        
        return false;
    }
};
```
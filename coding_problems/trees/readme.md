# Tree Problems

1. [In Order Traversal](#in-order-traversal)
1. [Pre Order Traversal](#pre-order-traversal)
1. [Post Order Traversal](#post-order-traversal)
1. [Invert Binary tree](#invert-binary-tree)
1. [Maximum Depth of Binary Tree](#maximum-depth-of-binary-tree)
1. [Diameter of Binary Tree](#diameter-of-binary-tree)
1. [Balanced Binary Tree](#balanced-binary-tree)
1. [Same Tree](#same-tree)
1. [Subtree of Another Tree](#subtree-of-another-tree)
1. [Lowest Common Ancestor of a Binary Search Tree](#lowest-common-ancestor-of-a-binary-search-tree)
1. [Insert into a Binary Search Tree](#insert-into-a-binary-search-tree)
1. [Delete Node in a BST](#delete-node-in-a-bst)
1. [Binary Tree Level Order Traversal](#binary-tree-level-order-traversal)
1. [Count Good Nodes in Binary Tree](#count-good-nodes-in-binary-tree)
1. [Valid Binary Search Tree](#valid-binary-search-tree)


## DFS
```cpp
void dfs(*root) {
    if (!root)
        return;

    // process pre order node
    dfs(root->left);
    // process in order node
    dfs(root->right);
    // process post order node
}
```
## BFS
```cpp
void bfs(*root) {
    queue<int> queue;

    queue.push(root);
    while (!q.empty()) {
        for ( i = q.size(); i >=0 ;i-- ) {
            node = q.front();
            q.pop();
            if (node) {
                q.push(node->left);
                q.push(node->right);
            }
        }
    }
}
```

### In Order Traversal
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

### Pre order Traversal
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

### Post order traversal
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

### Invert Binary tree
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

### Maximum Depth of Binary Tree
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

### Diameter of Binary Tree
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
### Balanced Binary Tree
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

### Same Tree
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
### Subtree of Another Tree
- call same tree on root && subRoot.
- if not than, check with left node of the main tree.
- then check wiht right node of the main tree.

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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!subRoot)
            return true;
        
        if (!root)
            return false;
        
        if (isSameTree(root, subRoot))
            return true;
            
        return isSubtree(root->left, subRoot)
            || isSubtree(root->right, subRoot);
    }

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

### Lowest Common Ancestor of a Binary Search Tree
- jmp to left if both nodes are small than root
- jmp to right if both nodes are greater than root
- else root is the ancestor node.
- if any of the nodes are null return nullptr

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q)
            return nullptr;
        
        if (p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);
        
        if (p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right, p, q);

        return root;
    }
};

```
### Insert into a Binary Search Tree
- if root is null return new node
- if smaller than root, root->left = insert(left)
- if larger than root. root->right = insert(right)

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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root)
            return new TreeNode(val);

        if (val < root->val)
            root->left = insertIntoBST(root->left, val);
        else 
            root->right = insertIntoBST(root->right, val);

        return root;       
    }
};
```

### Delete Node in a BST
- 3 types of nodes
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root)
            return root;
        // move left
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        // move right
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left)
                return root->right;
            if (!root->right)
                return root->left;

            // replace the root with largest no in left subtree
            // or smallest in right subtree
            TreeNode *cur = root->right;
            while (cur->left){
                cur = cur->left;
            }
            // move the left tree to side of smallest left
            cur->left = root->left;
            // root-> right will be the next root
            TreeNode *res = root->right;
            delete root;
            root = res;
        }

        return root;
    }
};
```

### Binary Tree Level Order Traversal
- Use BFS

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root)
            return res;
        
        queue<TreeNode*>q;
        q.push(root);

        while (!q.empty()) {
            vector<int> level;
            int size = q.size();

            for (int i = q.size(); i > 0; i--) {
                TreeNode *node = q.front();
                q.pop();

                if (node) {
                    level.push_back(node->val);
                    q.push(node->left);
                    q.push(node->right);
                }
            }

            if (!level.empty())
                res.push_back(level);
        }

        return res;
    }
};

```

### Binary Tree Right Side View
- BFS
- save the last node in every level
- push the last node val in res value

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
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> que;
        vector<int> res;
        TreeNode *node, *last_node;
        int sz;

        que.push(root);

        while (!que.empty()) {
            sz = que.size();
            last_node = nullptr;
            
            for (int i = 0; i < sz; i++) {
                node = que.front();
                que.pop();

                if (node) {
                    que.push(node->left);
                    que.push(node->right);

                    // cache the last_node
                    last_node = node;
                }
            }
            if (last_node)
                res.push_back(last_node->val);

        }

        return res;
    }
};

```

### Count Good Nodes in Binary Tree
- dfs preorder
- intial pass node and node-val as max val
- pass the max val seen so far while traversing. 
- if while traversing saw a new max val use that to traverse.
- have a counter in each node.

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
    int goodNodes(TreeNode* root) {
        return dfs(root, root->val);
    }

    int dfs(TreeNode *node, int max_nm) {
        if (!node)
            return 0;
        
        int res = (node->val >= max_nm) ? 1 : 0;
        max_nm = max(max_nm, node->val);

        res += dfs(node->left, max_nm);
        res += dfs(node->right, max_nm);

        return res;
    }
};

```

### Valid Binary Search Tree
- Valid BST is where right tree has all node > root node
- and left tree has all nodes < root node
- start wih long_min, long_max as the range.
- for each node check if the node is present in this range.
- when jmping to left, new max for the range is root->val.
- when jmping to right, new min will be root->val.

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
    bool isValidBST(TreeNode* root) {
        return valid(root, LONG_MIN, LONG_MAX);
    }

    bool valid(TreeNode *node, long left, long right) {
        if (!node)
            return true;

        // Check if the cur node is in between min and max
        if (!(left < node->val && node->val < right))
            return false;
        
        return (valid(node->left, left, node->val) &&
            valid(node->right, node->val, right));

    }
};

```
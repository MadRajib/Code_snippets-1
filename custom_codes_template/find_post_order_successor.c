#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHILDREN 10

// Tree Node Structure
typedef struct TreeNode {
    int data;
    struct TreeNode* parent;
    struct TreeNode* children[MAX_CHILDREN];
    int childCount;
} TreeNode;

// Function to create a new node
TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->parent = NULL;
    node->childCount = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Function to add child to a node
void addChild(TreeNode* parent, TreeNode* child) {
    if (parent->childCount < MAX_CHILDREN) {
        parent->children[parent->childCount++] = child;
        child->parent = parent;
    }
}

// Helper function to perform post-order traversal (for testing)
void postOrderTraversal(TreeNode* node, int* result, int* index) {
    if (node == NULL) return;

    for (int i = 0; i < node->childCount; i++) {
        postOrderTraversal(node->children[i], result, index);
    }
    result[(*index)++] = node->data;
}

// Helper function to find node by data (for testing)
TreeNode* findNode(TreeNode* root, int data) {
    if (root == NULL) return NULL;
    if (root->data == data) return root;

    for (int i = 0; i < root->childCount; i++) {
        TreeNode* found = findNode(root->children[i], data);
        if (found != NULL) return found;
    }
    return NULL;
}

// Function to print tree structure (for visualization)
void printTree(TreeNode* node, int level) {
    if (node == NULL) return;

    for (int i = 0; i < level; i++) printf("  ");
    printf("└─ %d\n", node->data);

    for (int i = 0; i < node->childCount; i++) {
        printTree(node->children[i], level + 1);
    }
}

// Function to free tree
void freeTree(TreeNode* node) {
    if (node == NULL) return;

    for (int i = 0; i < node->childCount; i++) {
        freeTree(node->children[i]);
    }
    free(node);
}

// ============================================
// MAIN FUNCTION TO IMPLEMENT
// ============================================
TreeNode* findPostOrderSuccessor(TreeNode* node) {

//     typedef struct TreeNode {
//      int data;
//      struct TreeNode* parent;
//      struct TreeNode* children[MAX_CHILDREN];
//      int childCount;
//     } TreeNode;

    // Sanity
    if (!node)
        return NULL;

    // case 1: no parent node
    if (!node->parent)
        return NULL;

    // case 2: if last sbiling
    TreeNode* parent = node->parent;
    if (parent->children[parent->childCount - 1] == node)
        return parent;

    // case 3: if has siblings
    int i = 0;
    for (; i < parent->childCount; i++) {
        if (parent->children[i] == node)
            break;
    }

    TreeNode* itr = parent->children[i + 1];
    while (itr->childCount) {
            itr = itr->children[0];
    }

    return itr;
}

// ============================================
// TEST FRAMEWORK
// ============================================
typedef struct TestCase {
    char* description;
    int nodeToFind;
    int expectedSuccessor; // -1 means NULL (no successor)
} TestCase;

// Build test tree 1
//       1
//      /|\
//     2 3 4
//    /|   |
//   5 6   7
TreeNode* buildTree1() {
    TreeNode* node1 = createNode(1);
    TreeNode* node2 = createNode(2);
    TreeNode* node3 = createNode(3);
    TreeNode* node4 = createNode(4);
    TreeNode* node5 = createNode(5);
    TreeNode* node6 = createNode(6);
    TreeNode* node7 = createNode(7);

    addChild(node1, node2);
    addChild(node1, node3);
    addChild(node1, node4);
    addChild(node2, node5);
    addChild(node2, node6);
    addChild(node4, node7);

    return node1;
}

// Build test tree 2
//       10
//      /  \
//     20  30
//    / \
//   40 50
TreeNode* buildTree2() {
    TreeNode* node10 = createNode(10);
    TreeNode* node20 = createNode(20);
    TreeNode* node30 = createNode(30);
    TreeNode* node40 = createNode(40);
    TreeNode* node50 = createNode(50);

    addChild(node10, node20);
    addChild(node10, node30);
    addChild(node20, node40);
    addChild(node20, node50);

    return node10;
}

// Build test tree 3 (single path)
//   100
//    |
//   200
//    |
//   300
TreeNode* buildTree3() {
    TreeNode* node100 = createNode(100);
    TreeNode* node200 = createNode(200);
    TreeNode* node300 = createNode(300);

    addChild(node100, node200);
    addChild(node200, node300);

    return node100;
}

// Build test tree 4 (single node)
TreeNode* buildTree4() {
    return createNode(42);
}

// Build test tree 5 (complex tree)
//         1
//       / | \
//      2  3  4
//     /|\    |\
//    5 6 7   8 9
//      |
//     10
TreeNode* buildTree5() {
    TreeNode* node1 = createNode(1);
    TreeNode* node2 = createNode(2);
    TreeNode* node3 = createNode(3);
    TreeNode* node4 = createNode(4);
    TreeNode* node5 = createNode(5);
    TreeNode* node6 = createNode(6);
    TreeNode* node7 = createNode(7);
    TreeNode* node8 = createNode(8);
    TreeNode* node9 = createNode(9);
    TreeNode* node10 = createNode(10);

    addChild(node1, node2);
    addChild(node1, node3);
    addChild(node1, node4);
    addChild(node2, node5);
    addChild(node2, node6);
    addChild(node2, node7);
    addChild(node4, node8);
    addChild(node4, node9);
    addChild(node6, node10);

    return node1;
}

void runTest(TreeNode* root, TestCase* test, int testNum) {
    printf("\n--- Test Case %d: %s ---\n", testNum, test->description);

    // Print tree structure
    printf("Tree Structure:\n");
    printTree(root, 0);

    // Get post-order traversal for reference
    int postOrder[100];
    int idx = 0;
    postOrderTraversal(root, postOrder, &idx);

    printf("\nPost-order Traversal: ");
    for (int i = 0; i < idx; i++) {
        printf("%d ", postOrder[i]);
    }
    printf("\n");

    // Find the node
    TreeNode* node = findNode(root, test->nodeToFind);
    if (node == NULL) {
        printf("❌ ERROR: Node %d not found in tree\n", test->nodeToFind);
        return;
    }

    printf("Finding successor of node: %d\n", test->nodeToFind);
    printf("Expected successor: %s\n",
           test->expectedSuccessor == -1 ? "NULL (no successor)" : "");
    if (test->expectedSuccessor != -1) {
        printf("Expected successor: %d\n", test->expectedSuccessor);
    }

    // Call the function
    TreeNode* successor = findPostOrderSuccessor(node);

    printf("Actual successor: ");
    if (successor == NULL) {
        printf("NULL\n");
    } else {
        printf("%d\n", successor->data);
    }

    // Validate
    bool passed = false;
    if (test->expectedSuccessor == -1 && successor == NULL) {
        passed = true;
    } else if (test->expectedSuccessor != -1 && successor != NULL &&
               successor->data == test->expectedSuccessor) {
        passed = true;
    }

    if (passed) {
        printf("✓ PASSED\n");
    } else {
        printf("❌ FAILED\n");
    }
}

int main() {
    printf("==============================================\n");
    printf("Post-order Successor in Tree - Test Suite\n");
    printf("==============================================\n");

    // Test Suite 1: Tree 1
    printf("\n========== Test Suite 1 ==========\n");
    TreeNode* tree1 = buildTree1();

    // Post-order: 5, 6, 2, 3, 7, 4, 1
    TestCase tests1[] = {
        {"Leaf node (5) -> successor is sibling's first unvisited (6)", 5, 6},
        {"Leaf node (6) -> successor is parent (2)", 6, 2},
        {"Internal node (2) -> successor is next sibling (3)", 2, 3},
        {"Leaf node (3) -> successor is first child of next sibling (7)", 3, 7},
        {"Leaf node (7) -> successor is parent (4)", 7, 4},
        {"Internal node (4) -> successor is root (1)", 4, 1},
        {"Root node (1) -> no successor", 1, -1}
    };

    for (int i = 0; i < 7; i++) {
        runTest(tree1, &tests1[i], i + 1);
    }
    freeTree(tree1);

    // Test Suite 2: Tree 2
    printf("\n========== Test Suite 2 ==========\n");
    TreeNode* tree2 = buildTree2();

    // Post-order: 40, 50, 20, 30, 10
    TestCase tests2[] = {
        {"Leaf node (40) -> successor is sibling (50)", 40, 50},
        {"Leaf node (50) -> successor is parent (20)", 50, 20},
        {"Internal node (20) -> successor is sibling (30)", 20, 30},
        {"Leaf node (30) -> successor is root (10)", 30, 10},
        {"Root node (10) -> no successor", 10, -1}
    };

    for (int i = 0; i < 5; i++) {
        runTest(tree2, &tests2[i], i + 8);
    }
    freeTree(tree2);

    // Test Suite 3: Single path
    printf("\n========== Test Suite 3 ==========\n");
    TreeNode* tree3 = buildTree3();

    // Post-order: 300, 200, 100
    TestCase tests3[] = {
        {"Leaf in chain (300) -> successor is parent (200)", 300, 200},
        {"Middle node (200) -> successor is root (100)", 200, 100},
        {"Root in chain (100) -> no successor", 100, -1}
    };

    for (int i = 0; i < 3; i++) {
        runTest(tree3, &tests3[i], i + 13);
    }
    freeTree(tree3);

    // Test Suite 4: Single node
    printf("\n========== Test Suite 4 ==========\n");
    TreeNode* tree4 = buildTree4();

    TestCase test4 = {"Single node tree -> no successor", 42, -1};
    runTest(tree4, &test4, 16);
    freeTree(tree4);

    // Test Suite 5: Complex tree
    printf("\n========== Test Suite 5 ==========\n");
    TreeNode* tree5 = buildTree5();

    // Post-order: 5, 10, 6, 7, 2, 3, 8, 9, 4, 1
    TestCase tests5[] = {
        {"Leaf (5) -> successor is next child (10)", 5, 10},
        {"Leaf with parent having more children (10) -> successor is parent (6)", 10, 6},
        {"Internal node (6) -> successor is next sibling (7)", 6, 7},
        {"Last child (7) -> successor is parent (2)", 7, 2},
        {"Node (2) -> successor is next sibling (3)", 2, 3}
    };

    for (int i = 0; i < 5; i++) {
        runTest(tree5, &tests5[i], i + 17);
    }
    freeTree(tree5);

    printf("\n==============================================\n");
    printf("Test Suite Complete\n");
    printf("==============================================\n");

    return 0;
}
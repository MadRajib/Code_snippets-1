#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Doubly Linked List Node Structure
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert at end (for test setup)
Node* insertEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Function to print the list
void printList(Node* head) {
    if (head == NULL) {
        printf("Empty list\n");
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to check if list is sorted
bool isSorted(Node* head) {
    if (head == NULL || head->next == NULL) {
        return true;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        if (temp->data > temp->next->data) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

// Function to convert list to array for comparison
int* listToArray(Node* head, int* size) {
    *size = 0;
    Node* temp = head;
    while (temp != NULL) {
        (*size)++;
        temp = temp->next;
    }
    
    int* arr = (int*)malloc((*size) * sizeof(int));
    temp = head;
    int i = 0;
    while (temp != NULL) {
        arr[i++] = temp->data;
        temp = temp->next;
    }
    return arr;
}

// Function to free the list
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// ============================================
// MAIN FUNCTION TO IMPLEMENT
// ============================================
Node* decreaseAndReinsert(Node* head, int C, int K) {
    // TODO: Implement this function
    // 1. Find the node with data = K
    // 2. Decrease its value by C (new value = K - C)
    // 3. Remove the node from current position
    // 4. Insert it at correct position to maintain sorted order
    // 5. Return the new head of the list
    
    
    return head;
}

// ============================================
// TEST FRAMEWORK
// ============================================
typedef struct TestCase {
    int* input;
    int inputSize;
    int C;
    int K;
    int* expected;
    int expectedSize;
    char* description;
} TestCase;

void runTest(TestCase* test, int testNum) {
    printf("\n--- Test Case %d: %s ---\n", testNum, test->description);
    
    // Create input list
    Node* head = NULL;
    for (int i = 0; i < test->inputSize; i++) {
        head = insertEnd(head, test->input[i]);
    }
    
    printf("Input List: ");
    printList(head);
    printf("C = %d, K = %d\n", test->C, test->K);
    
    printf("Expected Output: ");
    for (int i = 0; i < test->expectedSize; i++) {
        printf("%d ", test->expected[i]);
    }
    printf("\n");
    
    // Call the function
    head = decreaseAndReinsert(head, test->C, test->K);
    
    printf("Actual Output: ");
    printList(head);
    
    // Validate output
    int outputSize;
    int* output = listToArray(head, &outputSize);
    
    bool passed = true;
    
    // Check if list is sorted
    if (!isSorted(head)) {
        printf("❌ FAILED: List is not sorted!\n");
        passed = false;
    }
    
    // Check size
    if (outputSize != test->expectedSize) {
        printf("❌ FAILED: Size mismatch (expected %d, got %d)\n", 
               test->expectedSize, outputSize);
        passed = false;
    } else {
        // Check elements
        for (int i = 0; i < outputSize; i++) {
            if (output[i] != test->expected[i]) {
                printf("❌ FAILED: Element mismatch at index %d (expected %d, got %d)\n", 
                       i, test->expected[i], output[i]);
                passed = false;
                break;
            }
        }
    }
    
    if (passed) {
        printf("✓ PASSED\n");
    }
    
    free(output);
    freeList(head);
}

int main() {
    printf("==============================================\n");
    printf("Sorted Doubly Linked List - Test Suite\n");
    printf("==============================================\n");
    
    // Test Case 1: Basic case
    int input1[] = {10, 20, 30, 40, 50};
    int expected1[] = {10, 15, 20, 40, 50};
    TestCase test1 = {input1, 5, 15, 30, expected1, 5, "Decrease middle element"};
    runTest(&test1, 1);
    
    // Test Case 2: Move to beginning
    int input2[] = {5, 15, 25, 35};
    int expected2[] = {5, 10, 15, 35};
    TestCase test2 = {input2, 4, 15, 25, expected2, 4, "Move element to middle"};
    runTest(&test2, 2);
    
    // Test Case 3: Element at head
    int input3[] = {10, 20, 30, 40};
    int expected3[] = {5, 20, 30, 40};
    TestCase test3 = {input3, 4, 5, 10, expected3, 4, "Decrease head element"};
    runTest(&test3, 3);
    
    // Test Case 4: Element at tail
    int input4[] = {5, 10, 15, 20};
    int expected4[] = {5, 10, 12, 15};
    TestCase test4 = {input4, 4, 8, 20, expected4, 4, "Decrease tail element"};
    runTest(&test4, 4);
    
    // Test Case 5: Move to beginning (smallest)
    int input5[] = {20, 30, 40, 50};
    int expected5[] = {10, 30, 40, 50};
    TestCase test5 = {input5, 4, 10, 20, expected5, 4, "Move to beginning"};
    runTest(&test5, 5);
    
    // Test Case 6: Stay at end
    int input6[] = {10, 20, 30, 40};
    int expected6[] = {10, 20, 30, 35};
    TestCase test6 = {input6, 4, 5, 40, expected6, 4, "Stay at end"};
    runTest(&test6, 6);
    
    // Test Case 7: Single element
    int input7[] = {25};
    int expected7[] = {15};
    TestCase test7 = {input7, 1, 10, 25, expected7, 1, "Single element list"};
    runTest(&test7, 7);
    
    // Test Case 8: Two elements
    int input8[] = {10, 30};
    int expected8[] = {10, 20};
    TestCase test8 = {input8, 2, 10, 30, expected8, 2, "Two elements - decrease second"};
    runTest(&test8, 8);
    
    printf("\n==============================================\n");
    printf("Test Suite Complete\n");
    printf("==============================================\n");
    
    return 0;
}
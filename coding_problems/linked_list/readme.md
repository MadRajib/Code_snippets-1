# Linked List Problem

1. [Reverse A Linked List](#reverse-a-linked-list)
1. [Merge Two Sorted Linked Lists](#merge-two-sorted-linked-lists)
1. [Linked List Cycle Detection](#linked-list-cycle-detection)
1. [Reorder Linked List](#reorder-linked-list)

### Reverse A Linked List
- prev = nullptr
- cur = head
- while cur is valid
- save the next node
- cur->next = prev
- move pre to cur
- move cur to next
- return prev

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *prev, *cur, *next;

        next = nullptr;
        prev = nullptr;
        cur = head;

        while (cur) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        
        return prev;
    }
};
```
### Merge Two Sorted Linked Lists

- have a sentinal node and ptr pointing to it.
- ptr->next = next smaller element of list1 or list2
- increment list1 list2 ptr to next candidate
- move to next destination i.e ptr = ptr->next
- at last append the non empty list to the ptr->next
- return sentinal next

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode sentinal(0);
        ListNode *node = &sentinal;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                node->next = list1;
                list1 = list1->next;
            } else {
                node->next = list2;
                list2 = list2->next;
            }

            node = node->next;
        }

        if (list1)
            node->next = list1;
        else
            node->next = list2;

        return sentinal.next;
    }
};

```

### Linked List Cycle Detection
- slow and fast pointer
- if fast pointer reaches null then no cycle
- else slow and fast will be the same
```cpp
class Solution {
public:
    bool hasCycle(ListNode* head) {
        bool res = false;
        ListNode *slow, *fast;
        if (!head)
            return false;

        slow = head;
        fast = head->next;

        while (slow != fast) {
            if (!fast || !fast->next)
                break;
            slow = slow->next;
            fast = fast->next->next;
        }

        if (slow == fast)
            res = true;

        return res;
    }
};
```

### Reorder Linked List

Observation:
- final output : second half reversed and added to first list.
- find mid using slow and fast
- reverse the second half;
- move the nodes from second half to first half one by one

```cpp
class Solution {
public:
    ListNode * findMid(ListNode *head) {
        ListNode *slow, *fast;
        if (!head )
            return head;

        slow = head;
        fast = head->next;

        while (fast != nullptr
            && fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next->next;
        }

        return slow;
    }

    ListNode * reverseList(ListNode* head) {
        ListNode *prev, *cur, *next;
        if (!head)
            return nullptr;
    
        prev = nullptr;
        cur = head;
        while (cur != nullptr) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        return prev;
    }

    void reorderList(ListNode* head) {
        ListNode *mid;
        ListNode *next_half;
        ListNode *tmp1, *tmp2, *tmp;
        
        mid = findMid(head);
        next_half = mid->next;
        mid->next = nullptr;

        next_half = reverseList(next_half);
         
        head = head;
        while (next_half != nullptr) {
            tmp1 = head->next;
            tmp2 = next_half->next;
            
            // remove node from next half and add it first
            next_half->next = tmp1;
            head->next = next_half; 

            head = tmp1;
            next_half = tmp2;
        }
    }
};

```
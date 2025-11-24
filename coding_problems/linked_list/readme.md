# Linked List Problem

1. [Reverse A Linked List](#reverse-a-linked-list)
1. [Merge Two Sorted Linked Lists](#merge-two-sorted-linked-lists)

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
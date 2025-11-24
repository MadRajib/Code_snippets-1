# Linked List Problem

1. [Reverse A Linked List](#reverse-a-linked-list)

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

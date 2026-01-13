# Linked List Problem

1. [Reverse A Linked List](#reverse-a-linked-list)
1. [Merge Two Sorted Linked Lists](#merge-two-sorted-linked-lists)
1. [Linked List Cycle Detection](#linked-list-cycle-detection)
1. [Intersection of Two Linked Lists](#intersection-of-two-linked-lists)
1. [Reorder Linked List](#reorder-linked-list)
1. [Remove Node From End of Linked List](#remove-node-from-end-of-linked-list)
1. [Copy Linked List with Random Pointer](#copy-linked-list-with-random-pointer)
1. [Find the Duplicate Number](#find-the-duplicate-number)
1. [Reverse Linked List II](#reverse-linked-list-ii)
1. [LRU Cache](#lru-cache)
1. [LFU Cache](#lfu-cache)
1. [Merge K Sorted list](#merge-k-sorted-list)
1. [Insert Greatest Common Divisors in Linked List](#insert-greatest-common-divisors-in-linked-list)

## Interview Questions
1. [Decrease Node and Reinsert in Sorted DLL](#decrease-node-and-reinsert-in-sorted-dll)

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

        while (fast && fast->next) {
            if (slow == fast)
                return true;

            fast = fast->next->next;
            slow = slow->next;
        }
        
        return false;
    }
};
```

### Intersection of Two Linked Lists
> Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null.

For example, the following two linked lists begin to intersect at node c1:
```bash
Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'

Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Intersected at '2'

Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: No intersection

```

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
          ListNode *p1 = headA;
        ListNode *p2 = headB;
        
        if (p1 == NULL || p2 == NULL) return NULL;

        while (p1 != p2) {
            p1 = p1->next;
            p2 = p2->next;
            if (p1 == p2) return p1;
   
            if (p1 == NULL) p1 = headB;
            if (p2 == NULL) p2 = headA;
        }
        return p1;
        
        
    }
};
```

### Reorder Linked List
> You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln

Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …

You may not modify the values in the list's nodes. Only nodes themselves may be changed.

```bash
Example 1:
Input: head = [1,2,3,4]
Output: [1,4,2,3]

Example 2:

Input: head = [1,2,3,4,5]
Output: [1,5,2,4,3]
```

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

### Remove Node From End of Linked List
> Given the head of a linked list, remove the nth node from the end of the list and return its head.

```bash
Example 1:

Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]


Example 2:

Input: head = [1], n = 1
Output: []

Example 3:

Input: head = [1,2], n = 1
Output: [1]
```

- if we move a ptr from nth loc from start and another from start
- when ptr reaches the end, another pointer reaches nth location from last.
- but we want to remove it, so lets have a sentinal pointer and start the another pointer from it.
- this way when ptr reaches end, another will reach a node
prior to the deletion node.

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *n_ptr, *tmp, *next;
        ListNode sentinal(0);
        if (!head)
            return nullptr;
        
        sentinal.next = head;
        tmp = head;
        while (n > 0) {
            tmp = tmp->next;
            n--;
        }

        n_ptr = &sentinal;
        while (tmp != nullptr) {
            n_ptr = n_ptr->next;
            tmp = tmp->next;
        }

        // now n_ptr is pointing to nth + 1 node from last
        tmp = n_ptr;
        n_ptr = n_ptr->next;
        next = n_ptr->next;
        n_ptr->next = nullptr;
        free(n_ptr);
        tmp->next = next;

        return sentinal.next;
    }
};
```

### Copy Linked List with Random Pointer
> A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not point to any node.
Your code will only be given the head of the original linked list.

 
```bash
Example 1:


Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Example 2:


Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Example 3:



Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]
```

- have sentinal node for the new list
- use hash map to store old node -> new node mapping.
- save old random ptr value in new pointer random value to use it to point to new nodes
- iterate over the new list and set itr->random = mp[itr->random (old node ptr)]

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> mp;
        Node *temp, *prev, *itr;
        Node sentinal(0);

        if (!head)
            return nullptr;

        itr = head;
        prev = &sentinal;

        while (itr != nullptr) {
            temp = new Node(itr->val);
            temp->random = itr->random;
            prev->next = temp;
            prev = temp;
            mp[itr] = temp;
            itr = itr->next;
        }
        itr = sentinal.next;
        while (itr != nullptr) {
            itr->random = mp[itr->random];
            itr = itr->next;
        }

        return sentinal.next;
    }
};
```

### Add Two Numbers
> You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

```bash
Example 1:

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Example 2:

Input: l1 = [0], l2 = [0]
Output: [0]

Example 3:

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
- have a sentinal node makes it easy
```

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *itr1, *itr2, *prev, *temp;
        ListNode sentinal(0);
        int c = 0, sm;

        itr1 = l1;
        itr2 = l2;
        prev = &sentinal;

        while (itr1 != nullptr && itr2 != nullptr) {
            temp = new ListNode(0);
            sm = itr1->val + itr2->val + c;
            temp->val = sm % 10;
            c = sm / 10;
            prev->next = temp;
            prev = temp;

            itr1 = itr1->next;
            itr2 = itr2->next;
        }

        itr1 = (itr1 != nullptr) ? itr1 : itr2;

        while (itr1 != nullptr) {
            temp = new ListNode(0);
            sm = itr1->val + c;
            temp->val = sm % 10;
            c = sm /10;
            prev->next = temp;
            prev = temp;

            itr1 = itr1->next; 
        }

        if (c) {
            temp = new ListNode(0);
            temp->val = c;
            prev->next = temp;
        }

        return sentinal.next;
    }
};

```

### Find the Duplicate Number
> Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and using only constant extra space.

 
```bash
Example 1:

Input: nums = [1,3,4,2,2]
Output: 2

Example 2:

Input: nums = [3,1,3,4,2]
Output: 3

Example 3:

Input: nums = [3,3,3,3,3]
Output: 3
```
- consider each value in array to be a pointer pointing to next pointer
- slow and fast pointer
- to point to the start of the cycle move another pointer from 0 and slow from the intersection of fast and slow
- step by step, they will meet both will be equal
```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;

        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];

            if (slow == fast)
                break;
        }

        int slow2 = 0;
        while (true) {
            slow = nums[slow];
            slow2 = nums[slow2];
            if (slow == slow2)
                break;
        }

        return slow;
    }
};

```

### Reverse Linked List II
> Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.

```bash
Example 1:

Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
Example 2:

Input: head = [5], left = 1, right = 1
Output: [5]
```

- use sentinal
```cpp
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *cur, *leftPrev, *next, *fhead;
        ListNode sentinal(0);

        if (!head)
            return nullptr;
        
        sentinal.next = head;

        cur = head;
        leftPrev = &sentinal;
        for (int i = 0; i < left - 1; ++i) {
            leftPrev = cur;
            cur = cur->next;
        }

        ListNode *prev = nullptr;
        for (int i = 0; i < right - left +1; i++) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        leftPrev->next->next = cur;
        leftPrev->next = prev;

        return sentinal.next;
    }
};
```

### LRU Cache
> Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.

 
```bash
Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
```

Approach:
- DLL to store the nodes
- most used nodes always at the end
- least recently used will be in front 
- hash map to know if the node is present or not
- count and capacity variables

Push (key, val)
- While pushing a key,value to the cache
    - check if the node is present or not using a hash map
    - if present, move the node to the last and update its value
    - if not, check if cache is full ?
        - if yes remove the first node
    - then create a new node
        - add to the hash table
        - append to the list

Get (key)
- Check if cache is empty
- Check in hash map if key is present
    - if present, move the node to last
    - return its value

```cpp
class LRUCache {
private:
    struct ListNode {
        int key;
        int val;
        ListNode *prev;
        ListNode *next;
    };

    ListNode start_senti;
    ListNode end_senti;

    int capacity = 0;
    int count = 0;
    unordered_map<int, ListNode *> mp;
    
    void unplug(ListNode *node) {

        node->prev->next = node->next;
        node->next->prev = node->prev;

        node->next = nullptr;
        node->prev = nullptr;
    }

    void append(ListNode *node) {
        if (node == nullptr)
            return;
        node->prev = this->end_senti.prev;
        node->next = &(this->end_senti);

        this->end_senti.prev->next = node;
        this->end_senti.prev = node;
    }

    void update(ListNode *node) {
        if (node == nullptr)
            return;
        unplug(node);
        append(node);
    }

    void pop_front() {
        if (this->count == 0)
            return;
        
        ListNode *node = this->start_senti.next;
        this->start_senti.next = node->next;
        node->next->prev = &(this->start_senti);

        node->prev = nullptr;
        node->next = nullptr;

        mp.erase(node->key);
        this->count--;
    }

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->count = 0;
    
        this->start_senti.next = &(this->end_senti);
        this->end_senti.prev = &(this->start_senti);
    }
    
    int get(int key) {
        ListNode *node = nullptr;
        if (mp.find(key) == mp.end() || this->count == 0)
            return -1;
        
        node = mp[key];
        update(node);
        return node->val;
    }
    
    void put(int key, int value) {
        ListNode *node = nullptr;
        if (mp.find(key) != mp.end()) {
            node = mp[key];
            update(node);
            node->val = value; 
            return;
        }

        if (this->count == this->capacity)
            pop_front();

        node = new ListNode;
        node->key = key;
        node->val = value;
        mp[key] = node;
        append(node);

        this->count++;
    }
};
```

### LFU Cache
- A DLL for each frequency (freq → DLL)
    - Most recently used node of a frequency at the front
    - Least recently used node of a frequency at the end
- A hash map to know if a key exists
- minFreq helps to evict the correct node
- capacity and size tracking

put (key, val):
- Check for valid capactiy
- if key exits
    - update value
    - update count list for that node
- if no:
    - check if cache is full
        -  if yes:
        -  get the sentinal from minf
        -  remove senti->prev this is the last node
        -  remove the list if DLL became null
        - reduce size
    - Create a new node and add to hash map
    - since its a new node add the node to count(1) list
    - else create a new list for count(1) and add to it
- set the min freq = 1
- increase the size

Get (key):
- If not found → return -1
- Increase frequency of node
- update count list for that node
- Return value

update_node_list(node)
- save the old_count of the node
- and new_count as well
- if old count LL is present
    - unplug the node from that list
    - check if the old list is empty then erase the entry
    - if the old count was the min frequence increase it
- if new count LL is present add to that LL
- lese create a new LL for the new count and append

Push:
- 
```cpp
class LFUCache {
private:
    struct ListNode {
        int key;
        int val;
        int count;
        ListNode *prev;
        ListNode *next;

        ListNode() : key(0), val(0), count(0), prev(this), next(this) {}
    };

    int capacity = 0;
    int sz = 0;
    int minf = 0;

    unordered_map<int, ListNode *> kn_map;  // key -> node
    unordered_map<int, ListNode *> cL_map;  // freq -> sentinel

    void push_node(ListNode *senti, ListNode *node) {
        node->next = senti->next;
        node->prev = senti;
        senti->next->prev = node;
        senti->next = node;
    }

    void unplug_node(ListNode *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = node->prev = nullptr;
    }

    void update_count_list(ListNode *node) {
        int old_count = node->count;
        int new_count = old_count + 1;

        // unplug from old list
        if (cL_map.count(old_count)) {
            unplug_node(node);

            ListNode *senti = cL_map[old_count];
            // if old list becomes empty
            if (senti->next == senti) {
                delete senti;
                cL_map.erase(old_count);
                if (minf == old_count)
                    minf++;
            }
        }

        // create new list if missing
        if (!cL_map.count(new_count)) {
            ListNode *senti = new ListNode();
            cL_map[new_count] = senti;
        }

        node->count = new_count;
        push_node(cL_map[new_count], node);
    }

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        this->sz = 0;
        this->minf = 1;
    }

    int get(int key) {
        if (!capacity || !kn_map.count(key))
            return -1;

        ListNode *node = kn_map[key];
        update_count_list(node);
        return node->val;
    }

    void put(int key, int value) {
        if (!capacity)
            return;

        // update existing
        if (kn_map.count(key)) {
            ListNode *node = kn_map[key];
            node->val = value;
            update_count_list(node);
            return;
        }

        // evict if full
        if (sz == capacity) {
            ListNode *senti = cL_map[minf];
            ListNode *victim = senti->prev;  // LRU inside min frequency list

            unplug_node(victim);
            kn_map.erase(victim->key);
            delete victim;

            if (senti->next == senti) {
                delete senti;
                cL_map.erase(minf);
            }

            sz--;
        }

        // new node
        ListNode *node = new ListNode();
        node->key = key;
        node->val = value;
        node->count = 1;

        kn_map[key] = node;

        if (!cL_map.count(1))
            cL_map[1] = new ListNode();

        push_node(cL_map[1], node);

        minf = 1;
        sz++;
    }
};
```

### Merge K Sorted list
> You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

```bash
Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted linked list:
1->1->2->3->4->4->5->6
Example 2:

Input: lists = []
Output: []
Example 3:

Input: lists = [[]]
Output: []
```bash

```cpp
class Solution {
private:
    ListNode* mergeList(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* tail = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        if (l1) {
            tail->next = l1;
        }
        if (l2) {
            tail->next = l2;
        }

        return dummy.next;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }

        while (lists.size() > 1) {
            vector<ListNode*> mergedLists;
            for (int i = 0; i < lists.size(); i += 2) {
                ListNode* l1 = lists[i];
                ListNode* l2 = (i + 1) < lists.size() ? lists[i + 1] : nullptr;
                mergedLists.push_back(mergeList(l1, l2));
            }
            lists = mergedLists;
        }
        return lists[0];
    }
};

```
### Reverse Nodes in K-Group
> You are given the head of a singly linked list head and a positive integer k.

You must reverse the first k nodes in the linked list, and then reverse the next k nodes, and so on. If there are fewer than k nodes left, leave the nodes as they are.

Return the modified list after reversing the nodes in each group of k.

You are only allowed to modify the nodes' next pointers, not the values of the nodes.
```bash
Input: head = [1,2,3,4,5,6], k = 3

Output: [3,2,1,6,5,4]

Input: head = [1,2,3,4,5], k = 3

Output: [3,2,1,4,5]
```

Approach:
- Have a sentinel node
- jump to kth node from sentinel
    - kth = get_kth(groupPrev, k);
- reverse till kth->next
- tmp = groupPrev->next;
- groupPrev->next = kth; 
- groupPrev = tmp;
- kth = get_kth(groupPrev, k);

```cpp
class Solution {
public:
    ListNode * get_kth(ListNode * ptr, int k) {
        while (ptr && k > 0) {
            ptr = ptr->next;
            k--;
        }
        return ptr;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode sentinal(0);
        sentinal.next = head;

        ListNode *groupPrev = &sentinal;
        ListNode *kth = get_kth(groupPrev, k);
        ListNode *prev, *itr, *groupNext, *tmp;

        while (kth != nullptr) {

            groupNext = kth->next;
            prev = kth->next;
            itr = groupPrev->next;
            while (itr != groupNext) {
                tmp = itr->next;
                itr->next = prev;

                prev = itr;
                itr = tmp;
            }

            tmp = groupPrev->next;
            groupPrev->next = kth;
            groupPrev = tmp;
            kth = get_kth(groupPrev, k);
        }

        return sentinal.next;
    }
};
```

### Insert Greatest Common Divisors in Linked List
> You are given the head of a linked list head, in which each node contains an integer value.

Between every pair of adjacent nodes, insert a new node with a value equal to the greatest common divisor of them.

Return the head of the linked list after insertion.

The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.

```bash
Example 1:
Input: head = [12,3,4,6]
Output: [12,3,3,1,4,2,6]

Example 2:
Input: head = [2,1]
Output: [2,1,1]
```

```cpp
class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* cur = head, temp;

        while (cur->next) {
            int n1 = cur->val;
            int n2 = cur->next->val;

            ListNode *n = new ListNode(_gcd(n1, n2));
            n->next = cur->next;
            cur->next = n;
            cur = n->next;
        }

        return head;
    }

    // Ecludian Elgo
    int _gcd(int a, int b) {
        int temp;
        while (b > 0) {
            temp = b;
            b = a % b;
            a = temp;
        }

        return a;
    }
};
```


## Interview Questions

### Decrease Node and Reinsert in Sorted DLL
> Given a sorted doubly link list and two numbers C and K. You need to decrease the info of node with data K by C and insert the new node formed at its correct position such that the list remains sorted.

To practice use: [Practice template](../../custom_codes_template/decrease_node_and_reinsert_in_sorted_dll.c)

Note:
- Handle edge cases
    - if single node
    - if K node is first or last
    - if C is zero

```c
Node* decreaseAndReinsert(Node* head, int C, int K) {
    
    if (!head || !C)
        return head;
    
    Node *itr = head;
    Node *temp = NULL;
    
    while (itr && itr->data != K)
        itr = itr->next;
    
    // if no node found
    if (!itr)
        return head;
    
    // first node
    if (!itr->prev) {
        itr->data -= C;
        return head;
    }

    itr->prev->next = itr->next;
    // if last node
    if (itr->next) {
        itr->next->prev = itr->prev;
    }
    
    temp = itr;
    temp->data -= C;
    temp->next = NULL;
    
    itr = temp->prev;
    temp->prev = NULL;
    
    while (itr && itr->data > temp->data)
        itr = itr->prev;
    
    if (!itr) { // insert at the front
        temp->next = head;
        head->prev = temp;
        head = temp;
    } else {
        temp->next = itr->next;
        temp->prev = itr;
        itr->next = temp;
    }
    
    return head;
}
```
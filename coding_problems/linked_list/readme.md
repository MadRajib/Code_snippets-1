# Linked List Problem

1. [Reverse A Linked List](#reverse-a-linked-list)
1. [Merge Two Sorted Linked Lists](#merge-two-sorted-linked-lists)
1. [Linked List Cycle Detection](#linked-list-cycle-detection)
1. [Reorder Linked List](#reorder-linked-list)
1. [Remove Node From End of Linked List](#remove-node-from-end-of-linked-list)
1. [Copy Linked List with Random Pointer](#copy-linked-list-with-random-pointer)
1. [Find the Duplicate Number](#find-the-duplicate-number)
1. [Reverse Linked List II](#reverse-linked-list-ii)
1. [LRU Cache](#lru-cache)
1. [LFU Cache](#lfu-cache)

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

### Remove Node From End of Linked List
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
- have a sentinal node makes it easy

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
Approach:
- DLL to store the nodes
- most used notes always at the end
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